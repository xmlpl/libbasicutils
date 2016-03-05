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

  cout << "Releasing smartPtr1." << endl;
  smartPtr1.release();
  cout << "Releasing smartPtr2." << endl;
  smartPtr1.release();
  return 0;
}
