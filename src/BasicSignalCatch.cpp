#include "BasicSignalCatch.h"

template <int S>
BasicSignalCatch<S> *BasicSignalCatch<S>::top = 0;


template <int S>
BasicSignalCatch<S>::BasicSignalCatch() : prev(top), oldHandler(0),
					  armed(false) {
}

template <int S>
BasicSignalCatch<S>::~BasicSignalCatch() {
  unarm();
}


template <int S>
bool BasicSignalCatch<S>::arm() {
  top = this;
  oldHandler = signal(S, handler);  
  armed = true;

  return true;
}

template <int S>
void BasicSignalCatch<S>::unarm() {
  if (armed) {
    signal(S, oldHandler);
    top = prev;    
    armed = false;
  }
}

template <int S>
void BasicSignalCatch<S>::handler(int sig) {
  if (top) {
    signal(S, handler);
    siglongjmp(top->env, 1);
  }
}

template class BasicSignalCatch<SIGINT>;
template class BasicSignalCatch<SIGQUIT>;
template class BasicSignalCatch<SIGILL>;
template class BasicSignalCatch<SIGABRT>;
template class BasicSignalCatch<SIGFPE>;
template class BasicSignalCatch<SIGSEGV>;
template class BasicSignalCatch<SIGPIPE>;
template class BasicSignalCatch<SIGALRM>;
template class BasicSignalCatch<SIGUSR1>;
template class BasicSignalCatch<SIGUSR2>;
template class BasicSignalCatch<SIGCHLD>;
template class BasicSignalCatch<SIGCONT>;
template class BasicSignalCatch<SIGSTOP>;
template class BasicSignalCatch<SIGTSTP>;
template class BasicSignalCatch<SIGTTIN>;
template class BasicSignalCatch<SIGTTOU>;
