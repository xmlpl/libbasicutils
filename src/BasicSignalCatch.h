#ifndef BASICSIGNALCATCH_H
#define BASICSIGNALCATCH_H

#include <setjmp.h>
#include <signal.h>

template <int S>
class BasicSignalCatch {
  BasicSignalCatch<S> *prev;
  sighandler_t oldHandler;
  bool armed;

  static BasicSignalCatch<S> *top;
  
public:
  sigjmp_buf env;

  BasicSignalCatch();
  ~BasicSignalCatch();

  bool arm();
  void unarm();

protected:
  static void handler(int sig);
};

#define SIGNALED(x) (x.arm() && sigsetjmp(x.env, 1) != 0)
#endif // BASICSIGNALCATCH_H
