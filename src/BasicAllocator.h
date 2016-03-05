#ifndef BASICALLOCATOR_H
#define BASICALLOCATOR_H

#include "stdlib.h"

class BasicAllocator {
public:
  static void *alloc(size_t n) {return malloc(n);}
  static void *alloc_atomic(size_t n) {return malloc(n);}
  static void *calloc(size_t n) {return ::calloc(n, 1);}
  static void *realloc(void *p, size_t n) {return ::realloc(p, n);}
  static void free(void *p) {::free(p);}
};
#endif // BASICALLOCATOR_H
