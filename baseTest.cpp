#include <iostream>

struct Base {
  void foo() {
    non_virtual();
    virt();
  }

  void non_virtual() { std::cout << "base non_virtual\n"; }

  virtual void virt() { std::cout << "base virtual\n"; }
};

struct Derived : public Base {
  void non_virtual() { std::cout << "derived non_virual\n"; }

  virtual void virt() override { std::cout << "derived virtual\n"; }
};

int main(int argc, char *argv[]) {
  Derived d;
  Base b;
  b.foo();
  std::cout << "\n";
  d.foo();
}
