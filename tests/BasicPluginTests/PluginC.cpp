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

#include "Plugin.h"

#include <iostream>
#include <string>
using namespace std;

extern BasicPluginManager<Plugin> *manager;

class PluginA;
class PluginB;

class PluginC : public Plugin {
  Plugin *a;
  Plugin *b;

public:
  PluginC() {
    cout << "Constructing PluginC." << endl;

    a = manager->get("PluginA");
    b = manager->get("PluginB");
  }

  virtual ~PluginC() {
    cout << "Destructing PluginC" << endl;
  }

  virtual void f() {
    cout << "C" << endl;
    cout << "Calling Plugins A and B." << endl;
    a->f();
    b->f();
  }
};

BasicPluginProxy<Plugin, PluginC> proxy("PluginC", "Plugin C.", 2,
					(const char *[]){"PluginA", "PluginB"},
					manager);
