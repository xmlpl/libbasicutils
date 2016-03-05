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
#ifndef BASICTHREAD_H
#define BASICTHREAD_H

#include <pthread.h>
#include "BasicCondition.h"

struct BasicFunctorBase;

/// Provides an object orientated encapsulation of pthreads
/**
 * There are two was to use this class.
 * -# A class can inherit from BasicThread and implement the
 *  the virtual run() function.  This alows the object to have
 *  its own thread of execution.
 * -# A user can instantiate BasicThread passing in a pointer
 *  to a void *startRoutine(void *).  When the start function of
 *  of the thread object is called the startRoutine will be called
 *  with a new thread of execution.
 *
 *  The user has the ability to set a data variable which will be passed
 *  to the user function.  This void * is set to point to the BasicThread
 *  object itself by default.  This gives the user the ability to communicate
 *  data to the thread without using global data.
 */
class BasicThread : public BasicCondition {
  pthread_t thread;
  pthread_attr_t attr;

  BasicFunctorBase *functor;
  void *(*startRoutine)(void *);
  void *data;

 protected:
  bool shutdown;
  bool running;
  
 public:
  BasicThread();
  BasicThread(BasicFunctorBase *functor);
  BasicThread(void *(*startRoutine)(void *));
  virtual ~BasicThread();

  virtual void run();
  bool start();
  void stop();
  bool join();
  bool cancel();
  static void testCancel();
  bool detach();

  void *getData() {return data;}
  void setData(void *data) {this->data = data;}

  /** 
   * This function is not always necessary.  When a thread starts up
   * it will automaticly set running to true.  However if you are starting
   * a group of threads this function is useful so the starting threads
   * don't mistakenly think a thread has exited when it is actually just
   * starting up.  Before starting any threads in the group they can all
   * be set to started.  This gives the alusion that all the threads 
   * started at once.
   *
   * @param x True or False
   */
  void setRunning(bool x) {running = x;}
  bool isRunning() {return running;}
  bool shouldShutdown();

 private:
  virtual void onExit();
  virtual void onEntrance();
  static void *starter(void *me);

  void init();
};
#endif // BASICTHREAD_H
