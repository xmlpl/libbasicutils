#ifndef BASICGCALLOCATOR_H
#define BASICGCALLOCATOR_H

#include <gc/gc.h>

class BasicGCAllocator {
public:
  static void *alloc(size_t n) {return GC_MALLOC(n);}
  static void *alloc_atomic(size_t n) {return GC_MALLOC_ATOMIC(n);}
  static void *calloc(size_t n) {return GC_MALLOC(n);}
  static void *realloc(void *p, size_t n) {return GC_REALLOC(p, n);}
  static void free(void *p) {GC_FREE(p);}
};
#endif // BASICGCALLOCATOR_H
