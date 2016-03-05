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
#include "BasicCondition.h"

#ifndef WIN32
#include <sys/time.h>
#endif

#ifdef BASICCONDITION_DEBUG
#include <iostream>
using namespace std;
#endif

BasicCondition::BasicCondition() {
  pthread_cond_init(&cond, NULL);

#ifdef BASICCONDITION_DEBUG
  cout << "BasicCondition()" << endl;
#endif
}

BasicCondition::~BasicCondition() {
  pthread_cond_destroy(&cond);

#ifdef BASICCONDITION_DEBUG
  cout << "~BasicCondition()" << endl;
#endif
}

/** 
 * Alows the user to wait for BasicCondition to be signaled, but
 * with a time out value.  This usefull if you cannot always guarantee
 * a signal will come.
 * 
 * @param msec Timeout in milliseconds
 * 
 * @return true if signaled, false if timedout or an error occured.
 */
#ifndef WIN32 // Windows dosen't like the time functions.
bool BasicCondition::timedWait(int msec) {
  struct timeval now;
  struct timespec timeout;
  gettimeofday(&now, NULL);
  timeout.tv_sec = now.tv_sec + (msec / 1000);
  timeout.tv_nsec = (now.tv_usec + (msec % 1000) * 1000) * 1000;

  if (pthread_cond_timedwait(&cond, &mutex, &timeout)) return false;
  else return true;
}
#endif

