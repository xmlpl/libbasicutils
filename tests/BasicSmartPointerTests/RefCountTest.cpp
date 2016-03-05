#include <BasicUtils/BasicException.h>
#include <BasicUtils/BasicSmartPointer.h>

#include <iostream>
using namespace std;

class A {
public:
  A() {cout << "Constructor called." << endl;}
  ~A() {cout << "Destructor called." << endl;}
};

int main(int argc, char *argv[]) {
  BasicSmartPointer<A> smartPtr1 = new A;
  BasicSmartPointer<A> smartPtr2 = smartPtr1;
  BasicSmartPointer<A> smartPtr3 = smartPtr2;

  cout << "smartPtr1 ref count = " << smartPtr1.getRefCount() << endl;
  cout << "smartPtr2 ref count = " << smartPtr2.getRefCount() << endl;
  cout << "smartPtr3 ref count = " << smartPtr3.getRefCount() << endl;

  cout << "Releasing smartPtr1." << endl;
  smartPtr1.release();

  cout << "smartPtr1 ref count = " << smartPtr1.getRefCount() << endl;
  cout << "smartPtr2 ref count = " << smartPtr2.getRefCount() << endl;
  cout << "smartPtr3 ref count = " << smartPtr3.getRefCount() << endl;

  cout << "Releasing smartPtr2." << endl;
  smartPtr2.release();

  cout << "smartPtr1 ref count = " << smartPtr1.getRefCount() << endl;
  cout << "smartPtr2 ref count = " << smartPtr2.getRefCount() << endl;
  cout << "smartPtr3 ref count = " << smartPtr3.getRefCount() << endl;

  cout << "Releasing smartPtr3." << endl;
  smartPtr3.release();

  cout << "smartPtr1 ref count = " << smartPtr1.getRefCount() << endl;
  cout << "smartPtr2 ref count = " << smartPtr2.getRefCount() << endl;
  cout << "smartPtr3 ref count = " << smartPtr3.getRefCount() << endl;

  return 0;
}
