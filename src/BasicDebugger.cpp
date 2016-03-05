/*******************************************************************\

              Copyright (C) 2004 Joseph Coffland

    This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
             GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
                           02111-1307, USA.

            For information regarding this software email
                   jcofflan@users.sourceforge.net

\*******************************************************************/

#include "BasicDebugger.h"
#include "BasicProcess.h"
#include "BasicString.h"
#include "BasicException.h"

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

using namespace std;

string BasicDebugger::executableName;
int BasicDebugger::numTraces = 0;
bool BasicDebugger::leaveCores = false;
bool BasicDebugger::traceFiltering = true;
int BasicDebugger::maxTraces = 10;

void BasicDebugger::initStackTrace(string executableName) {
  BasicDebugger::executableName = executableName;
  BasicException::enableStackTraces = true;
}

bool BasicDebugger::printStackTrace(ostream &stream) {
  list<string> trace;
  bool retVal = getStackTrace(trace);

  list<string>::iterator it;
  for (it = trace.begin(); it != trace.end(); it++)
    stream << *it << endl;

  return retVal;
}

#define BUF_SIZE 2048

bool BasicDebugger::_getStackTrace(std::list<std::string> &trace) {
  if (executableName == "") {
    trace.push_back("Stack Trace Error: Stack dumper not initialized!");
    return false;
  }

  numTraces++;
  if (maxTraces && numTraces > maxTraces) {
    trace.push_back("Stack Trace Error: Exceeded maxTraces of " +
		    BasicString(maxTraces));
    return false;
  }

  // Set core ulimit
  struct rlimit coreLimit;
  getrlimit(RLIMIT_CORE, &coreLimit);
  coreLimit.rlim_cur = coreLimit.rlim_max;
  setrlimit(RLIMIT_CORE, &coreLimit);


  int pid = fork();
  
  // Fork child and dump core
  if (pid == 0) {
    abort(); // Dump core
    exit(0);

  } else if (pid == -1) {
    trace.push_back("Stack Trace Error: Creating abort process!");
    return false;
  }

  waitpid(pid, 0, 0);


  // Check for core file
  string coreFilename = "core";
  int coreFD = open(coreFilename.c_str(), O_RDONLY);
  if (coreFD == -1) {
    coreFilename = coreFilename + "." + BasicString(pid);
    coreFD = open(coreFilename.c_str(), O_RDONLY);

    if (coreFD == -1) {
      trace.push_back(string("Stack Trace Error: creating core file!\n") +
		      "This can occur if you do not have write permission\n" +
		      "in the current directory or if the core file limit\n" +
		      "is set to zero.  On many Unix systems the core file\n" +
		      "limit can be set with 'ulimit -c unlimited'.");

      return false;
    }
  }
  close(coreFD);


  // Spawn gdb process
  int argc = 0;
  char *argv[5];

  argv[argc++] = (char *)"gdb";
  argv[argc++] = (char *)executableName.c_str();
  argv[argc++] = (char *)"-c";
  argv[argc++] = (char *)coreFilename.c_str();
  argv[argc] = 0;

  try {
    BasicProcess debugProc;
    BasicPipe *inPipe = debugProc.getChildPipe(BasicProcess::TO_CHILD, 0);
    BasicPipe *outPipe = debugProc.getChildPipe(BasicProcess::FROM_CHILD, 1);
    BasicPipe *errPipe = debugProc.getChildPipe(BasicProcess::FROM_CHILD, 2);
    debugProc.exec(argv);

    // Run gdb commands
    string debugCmd =
      string("set width ") + BasicString(BUF_SIZE - 1) + "\nwhere\nquit\n";
    write(inPipe->getInFD(), debugCmd.c_str(), debugCmd.length());


    // Read output
    FILE *out = fdopen(outPipe->getOutFD(), "r");
    FILE *err = fdopen(errPipe->getOutFD(), "r");
    if (!out || !err) {
      trace.push_back("Stack Trace Error: Opening debugger output streams!");

      return false;
    }

    char buf[BUF_SIZE + 1];
    int offset = 0;
    int count = 0;
    while (fgets(buf, BUF_SIZE, out)) {
      if (buf[0] == '#') {

	if (traceFiltering) {
	  count++;
	  
	  if (strstr(buf, "BasicDebugger::") ||
	      strstr(buf, "BasicException::init") ||
	      strstr(buf, "BasicException (")) {
	    offset = count;
	    trace.clear();
	    continue;
	  }
	}

	int line = atoi(&buf[1]) - offset;
	char *start = strchr(buf, ' ');
	int len = strlen(buf);

	if (buf[len - 1] == '\n' || buf[len - 1] == '\r') buf[len - 1] = 0;
	trace.push_back(string("#") + BasicString(line) + start);
	}
    }
    while (fgets(buf, BUF_SIZE, err)) {
      int len = strlen(buf);
      if (buf[len - 1] == '\n' || buf[len - 1] == '\r') buf[len - 1] = 0;
      if (buf[0] != 0) trace.push_back(buf);
    }

    // Clean up
    fclose(out);
    fclose(err);

    if (!leaveCores) unlink(coreFilename.c_str());

    debugProc.wait();
    if (debugProc.getReturnCode()) {
      trace.push_back("Stack Trace Error: gdb returned an error.");

      return false;
    }

    return true;

  } catch (BasicException &e) {
    trace.push_back(string("Stack Trace Error: ") + e.getMessage());
  }

  return false;
}

bool BasicDebugger::getStackTrace(std::list<std::string> &trace) {
  static bool inStackTrace = false;
  bool ret;

  if (inStackTrace) {
    trace.push_back("Stack Trace Error: Already in stack trace!");
    return false;    
  }

  inStackTrace = true;

  try {
    ret = _getStackTrace(trace);

  } catch (...) {
    inStackTrace = false;
    throw;
  }
  inStackTrace = false;

  return ret;
}

#ifdef BASICDEBUGGER_TEST
#include <iostream>

void b (int x) {
  THROW("Test cause!");
}

void a(char *x) {
  try {
    b(10);
  } catch (BasicException &e) {
    THROWC("Test exception!", e);
  } 
}


int main(int argc, char *argv[]) {
  BasicDebugger::initStackTrace(argv[0]);

  try {
    
    a("test");

  } catch (BasicException &e) {
    cerr << "Exception: " << e << endl;
  }

  return 0;
}
#endif // BASICDEBUGGER_TEST
