/*******************************************************************\

              Copyright (C) 2003 Joseph Coffland

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

#include "BasicUtils/BasicPluginManager.h"
#include "BasicUtils/BasicPluginProxy.h"
#include "BasicUtils/BasicSmartPointer.h"
#include "BasicUtils/BasicException.h"

#include "Plugin.h"

#include <iostream>
using namespace std;

BasicPluginManager<Plugin> *manager;

int main(int argc, char *argv[]) {
  try {
    BasicSmartPointer<BasicPluginManager<Plugin> > m = manager =
      new BasicPluginManager<Plugin>;
    
    manager->loadLibrary(string(".libs/libPluginD") + 
			 BasicPluginManager<Plugin>::libExtension);
    manager->loadLibrary(string(".libs/libPluginE") +
			 BasicPluginManager<Plugin>::libExtension);
    manager->loadLibrary(string(".libs/libPluginF") +
			 BasicPluginManager<Plugin>::libExtension);

  } catch (BasicException &e) {
    e.print(cerr, false);
    cerr << endl;

    return 1;
  } catch (...) {
    cerr << "Caught unknown exception." << endl;

    return 1;
  }
  return 0;
}
