#include <BasicUtils/BasicException.h>
#include <BasicUtils/BasicSmartPointer.h>

#include <iostream>
using namespace std;

class A {
public:
  A() {cout << "Constructor called." << endl;}
  ~A() {cout << "Destructor called." << endl;}

  void test() {cout << "Test called." << endl;}
};

int main(int argc, char *argv[]) {
  BasicSmartPointer<A> smartPtr1 = new A;
  smartPtr1->test();

  return 0;
}
