#include <iostream>
#include <string>

class Foo {
public:
  std::string *s;
  Foo() {
    std::cout << "Foo ctor" << std::endl;
    s = new std::string("Woot");
  }

  void doit() { std::cout << "Woot" << std::endl; }

  ~Foo() {
    std::cout << "Foo dtor" << std::endl;
    delete s;
  }
};

int main(int argc, char *argv[]) {
  Foo f;
  // f.~Foo();
  f.doit();
}
