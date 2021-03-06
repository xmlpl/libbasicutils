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

#include "BasicClassGroupFactory.h"

#include "BasicClassFactoryBase.h"
#include "BasicClassAccessorBase.h"
#include "BasicClassGroup.h"

#include "BasicException.h"

BasicClassGroupFactory::~BasicClassGroupFactory() {
  for (unsigned int i = 0; i < classFactories.getSize(); i++)
    delete classFactories[i];
}

void BasicClassGroupFactory::registerClass(BasicClassAccessorBase *accessor) {
  int id = classFactories.put(accessor->createClassFactory());
  accessor->setId(id);
}

BasicClassGroup *BasicClassGroupFactory::create() {
  void **classes = new void *[classFactories.getSize()];

  for (unsigned int i = 0; i < classFactories.getSize(); i++)
    classes[i] = classFactories[i]->create();

  return new BasicClassGroup(classes, classFactories.getSize());
}

void BasicClassGroupFactory::destroy(BasicClassGroup *group) {
  ASSERT_OR_THROW("BasicClassGroupFactory NULL group pointer!", group);

  for (unsigned int i = 0; i < group->size; i++)
    classFactories[i]->destroy(group->classes[i]);

  delete group->classes;
  delete group;
}
