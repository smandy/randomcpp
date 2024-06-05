#include <iostream>

class Foo {
public:
  mutable int x;

  Foo() : x{} {}
};

int main(int argc, char *argv[]) {
  const Foo x{};
  x.x++;
  std::cout << "x is " << x.x << std::endl;
};
