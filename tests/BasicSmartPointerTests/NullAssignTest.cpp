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
  BasicSmartPointer<A> smartPtr = new A;

  cout << "NULLing smartPtr" << endl;
  smartPtr = NULL;
  cout << "smartPtr NULLed" << endl;
  return 0;
}
