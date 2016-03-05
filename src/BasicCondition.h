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
#ifndef BASICCONDITION_H
#define BASICCONDITION_H

#include <pthread.h>
#include <assert.h>

#include "BasicLockable.h"

///  BasicCondition provides an object orientated encapsulation of a pthread
///  mutex and condition variable.
/**
 * There are two basic methods of using this class.
 * -# A class can inherit from BasicCondition.  
 *    This alows code to lock on the inherited object itself.
 * -# The user can create instances of BasicCondition directly.
 */
class BasicCondition : public BasicLockable {
  pthread_cond_t cond;

 public:
  BasicCondition();
  ~BasicCondition();

  /// Wait for a signal indefinately
  void wait() {pthread_cond_wait(&cond, &mutex);}
#ifndef WIN32
  /// Wait for a signal no longer than msec milliseconds
  bool timedWait(int msec); // In milliseconds
#endif
  /// Signal one waiting process
  void signal() {pthread_cond_signal(&cond);}
  /// Signal all waiting processes
  void broadcast() {pthread_cond_broadcast(&cond);}
};

#endif // BASICCONDITION_H
