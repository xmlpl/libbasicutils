#ifndef BASICOBJCOUNTER_H
#define BASICOBJCOUNTER_H


#ifdef NO_BASICOBJCOUNTERS
template <class T>
class BasicObjCounter {};

#else

#include "BasicException.h"

#include <iostream>
#include <typeinfo>
#include <stdlib.h>

template <class T>
class BasicObjCounter {
  static unsigned int constructed;
  static unsigned int destructed;
  static bool atExitCalled;

public:
  BasicObjCounter() {
    if (!atExitCalled) {
      atexit(print);
      atExitCalled = true;
    }

    constructed++;
  }
  ~BasicObjCounter() {destructed++;}

  static unsigned int getConstructed() {return constructed;}
  static unsigned int getDestructed() {return destructed;}
  static void print() {
    std::cerr << typeid(T).name() << ": "
	      << constructed << " Constructed "
	      << destructed << " Destructed"
	      << std::endl;
  }
};

template <class T>
unsigned int BasicObjCounter<T>::constructed = 0;

template <class T>
unsigned int BasicObjCounter<T>::destructed = 0;

template <class T>
bool BasicObjCounter<T>::atExitCalled = false;

#endif // NO_BASICOBJCOUNTERS
#endif // BASICOBJCOUNTER_H
