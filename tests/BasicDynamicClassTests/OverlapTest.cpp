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

#include <BasicUtils/BasicDynamicClassFactory.h>
#include <BasicUtils/BasicDynamicClassNode.h>
#include <BasicUtils/BasicException.h>

#include <iostream>
#include <string>
using namespace std;


class A {
public:
  int x;
  int y;
  int z;
};

class B {
public:
  double r;
};

int main(int argc, char *argv[]) {
  try {
    BasicDynamicClassNode<A> aClassNode;
    BasicDynamicClassNode<B> bClassNode;

    BasicDynamicClassFactory factory;

    aClassNode.registerNode(&factory);
    bClassNode.registerNode(&factory);

    void *node = factory.create();

    bClassNode.get(node)->r = 12345.67;
    aClassNode.get(node)->x = -1;
    aClassNode.get(node)->y = -2;
    aClassNode.get(node)->z = -3;

    cout << "r=" << bClassNode.get(node)->r << " "
	 << "x=" << aClassNode.get(node)->x << " "
	 << "y=" << aClassNode.get(node)->y << " "
	 << "z=" << aClassNode.get(node)->z << endl;

    factory.destroy(node);
   
  } catch (BasicException &e) {
    cerr << e.getMessage() << endl;
    return 1;
  }

  return 0;
}
