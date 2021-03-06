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
#ifndef BASICDEBUGGER_H
#define BASICDEBUGGER_H

#include <string>
#include <iostream>
#include <list>

class BasicDebugger {
  static std::string executableName;
  static int numTraces;
public:
  static bool leaveCores;
  static bool traceFiltering;
  static int maxTraces;

  static void initStackTrace(std::string executableName);
  static bool printStackTrace(std::ostream &stream);
  static bool getStackTrace(std::list<std::string> &trace);
  static bool stackTraceInitialized() {return executableName != "";}

private:
  static bool _getStackTrace(std::list<std::string> &trace);
};
#endif // BASICDEBUGGER_H
