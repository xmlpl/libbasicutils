#ifndef BASICREFERENCE_H
#define BASICREFERENCE_H


#include <BasicUtils/BasicException.h>
#include <string>

template <class T>
class BasicReference;

template <class T>
class BasicReferenceable {
  unsigned int refCount;

public:
  BasicReferenceable() : refCount(0) {}
  ~BasicReferenceable() {
    ASSERT_OR_THROW("BasicReferenceable deleted, but outstanding references remain!",
		    refCount == 0);
  }

  void incRef() {refCount++;}
  void decRef() {refCount--; if (!refCount) delete this;}
  unsigned int getRefCount() const {return refCount;}
};


template <class T>
class BasicReference {
  T *ptr;

public:
  // Copy constructor
  BasicReference() : ptr(0) {}
  BasicReference(const BasicReference<T> &o) : ptr(o.ptr) {if (ptr) ptr->incRef();}
  BasicReference(T *ptr) : ptr(ptr) {if (ptr) ptr->incRef();}
  ~BasicReference() {release();}

  const bool operator==(const BasicReference<T> &ref) const {
    return ptr == ref.ptr;
  }

  const bool operator!=(const BasicReference<T> &ref) const {
    return ptr != ref.ptr;
  }

  const bool operator<(const BasicReference<T> &ref) const {
    return ptr < ref.ptr;
  }

  const bool operator<=(const BasicReference<T> &ref) const {
    return ptr <= ref.ptr;
  }

  const bool operator>(const BasicReference<T> &ref) const {
    return ptr > ref.ptr;
  }

  const bool operator>=(const BasicReference<T> &ref) const {
    return ptr >= ref.ptr;
  }

  BasicReference<T> &operator=(const BasicReference<T> &ref) {
    if (*this == ref) return *this;
    
    release();

    ptr = ref.ptr;
    if (ptr) ptr->incRef();

    return *this;
  }

  T *get() const {return ptr;}
  //T *operator()() const {return get();}
  T *operator->() const {checkPtr(); return get();}
  T &operator*() const {checkPtr(); return *get();}
  T &operator[](const unsigned int x) const {checkPtr(); return get()[x];}
  bool operator!() const {return ptr == 0;}

  void release() {
    if (ptr) {
      ptr->decRef();
      ptr = 0;
    }
  }

  T *adopt() {
    if (ptr && ptr->getRefCount() > 1)
      THROW("Cannot adopt a pointer with multiple references!");
	    
    if (ptr) ptr->decRef();
    T *tmp = ptr;
    ptr = 0;
    return tmp;
  }

  unsigned int getRefCount() const {return ptr ? ptr->getRefCount() : 0;}

protected:
  void checkPtr() const {
    ASSERT_OR_THROW("Cannot dereference null pointer!", ptr);
  }
};
#endif
