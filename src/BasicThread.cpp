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
#include "BasicThread.h"

#include "BasicFunctor.h"
#include "BasicException.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#ifdef BASICTHREAD_TEST
#include <unistd.h>

void *threadRoutine(void *thread) {
  printf("Entering threadRoutine\n");

  BasicThread *threadPtr = (BasicThread *)thread;

  int data = (int)threadPtr->getData();

  int i = 0;
  while (!threadPtr->shouldShutdown()) {
    printf("Thread %d running %d\n", data, i++);
    sleep(0);
  }

  printf("Leaving threadRoutine.\n");
  //  threadPtr->exit();

  return NULL; // Not reached
}

int main(int argc, char *argv[]) {
  int num = 0;
  if (argc > 1) num = atoi(argv[1]);
  if (!num) num = 2;

  BasicThread **testThreads = (BasicThread **)malloc(sizeof(void *) * num);

  int i;
  for (i = 0; i < num; i++) {
    printf("Starting thread %d\n", i);
    testThreads[i] = new BasicThread(threadRoutine);
    testThreads[i]->setData((void *)i);
    testThreads[i]->start();
  }

  getchar();

  for (i = 0; i < num; i++) {
    printf("Stopping thread %d\n", i);
    testThreads[i]->stop();
  }
  for (i = 0; i < num; i++) {
    printf("Joining thread %d\n", i);
    testThreads[i]->join();
  }

  return 0;
}
#endif


BasicThread::BasicThread() :
  functor(NULL), startRoutine(NULL) {
  init();
}

BasicThread::BasicThread(BasicFunctorBase *functor) : 
  functor(functor), startRoutine(NULL) {
  init();
}

BasicThread::BasicThread(void * (*startRoutine)(void *)) : 
  functor(NULL), startRoutine(startRoutine) {
  init();
}

BasicThread::~BasicThread() {
}

/** 
 * This function does initializations common to all the constructors.
 * It takes in a special consideration for SunOS to circumvent a bug
 * that occurs when more then one thread is started.
 */
void BasicThread::init() {
  data = this;
  running = false;

  pthread_attr_init(&attr);
#ifdef __sun__
  pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
#endif
}

/** 
 * Starts the thread.
 *
 */
bool BasicThread::start() {
  shutdown = false;
  if (pthread_create(&thread, &attr, starter, this)) {
    perror("BasicThread::start()");
    return false;
  }
  return true;
}

/** 
 * Requests the thread stop via the shutdown variable.
 * There is however no guarantee that the thread will
 * actually stop.  The running thread must check the
 * shutdown variable and decide to stop.
 */
void BasicThread::stop() {
  shutdown = true;
}

/** 
 * This causes the calling thread of execution to block
 * until the thread of this object exits.
 */
bool BasicThread::join() {
  if (pthread_join(thread, NULL)) return false;
  return true;
}

bool BasicThread::cancel() {
  if (pthread_cancel(thread)) return false;
  running = false;
  return true;
}

void BasicThread::testCancel() {
  pthread_testcancel();
}

bool BasicThread::detach() {
  if (pthread_detach(thread)) return false;
  return true;
}

/** 
 * This function should be called from the thread
 * itself to determine if shutdown has been requested.
 * If a thread doesn't monitor this variable stop() will
 * not work!
 *
 * @return True if shutdown has been requested
 */
bool BasicThread::shouldShutdown() {
  return shutdown;
}

/** 
 * This virtual function can be overriden by inheriting classes
 * which would like to do some extra processing on thread exit.
 * It is called by BasicThread just after either the overriden
 * run() or startRoutine function returns.
 */
void BasicThread::onExit() {
}

/** 
 * This virtual function can be overriden by inheriting classes
 * which would like to do some extra processing before thread startup.
 * It is called by BasicThread just before either the overriden
 * run() or startRoutine function is called.
 */
void BasicThread::onEntrance() {
}

/** 
 * This static function should never be called directly.
 * It is used by pthreads in starting the thread.
 * 
 * @param me A this pointer
 * 
 * @return Nothing
 */
void *BasicThread::starter(void *me) {
  BasicThread *thisObj = (BasicThread *)me;
  thisObj->running = true;
  
  try {
    thisObj->onEntrance();
  } catch (BasicException &e) {
    cerr << "Exception in thread onEntrance(): " << e << endl;
  } catch (...) {
    cerr << "Unknown exception in thread onEntrance()" << endl;
  }

  try {
    if (thisObj->startRoutine) {
      (*thisObj->startRoutine)(thisObj);
    } else if (thisObj->functor) {
      (*thisObj->functor)();
    } else thisObj->run();

  } catch (BasicException &e) {
    cerr << "Exception in thread: " << e << endl;
  } catch (...) {
    cerr << "Unknown exception in thread" << endl;
  }

  try {
    thisObj->onExit();
  } catch (BasicException &e) {
    cerr << "Exception in thread onExit(): " << e << endl;
  } catch (...) {
    cerr << "Unknown exception in thread onExit()" << endl;
  }

  thisObj->running = false;
  pthread_exit(0);
  return NULL;  // Not reached
}

/** 
 * This virtual function should be overriden by inheriting
 * process.  This function is called by BasicThread from within
 * the new thread of execution after start() is called.
 */
void BasicThread::run() {
  printf("BasicThread:run() Not Implemented\n");
}
