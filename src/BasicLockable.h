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
#ifndef BASICLOCKABLE_H
#define BASICLOCKABLE_H

#include <pthread.h>

#ifdef BASICLOCKABLE_DEBUG
#include <iostream>
#endif

///  BasicLockable provides an object orientated encapsulation of a pthread
///  mutex.
/**
 * There are two basic methods of using this class.
 * -# A class can inherit from BasicLockable.  
 *    This alows code to lock on the inherited object itself.
 * -# The user can create instances of BasicLockable directly.
 */
class BasicLockable {
 protected:
  pthread_mutex_t mutex;

 public:
  BasicLockable();
  ~BasicLockable();

  /// Lock the mutex
  void lock() {
#ifdef BASICLOCKABLE_DEBUG
    std::cout << "Basiclockable::lock()" << std::endl;
#endif
    pthread_mutex_lock(&mutex);
  }
  /// Unlock the mutex
  void unlock() {
    pthread_mutex_unlock(&mutex);
#ifdef BASICLOCKABLE_DEBUG
    std::cout << "Basiclockable::unlock()" << std::endl;
#endif
  }
};
#endif // BASICLOCKABLE_H
