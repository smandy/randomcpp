#include <iostream>

struct Foo {
  int x;
};

void process(Foo &lval) { std::cout << "Lvalue" << std::endl; }

void process(Foo &&rval) { std::cout << "rvalue" << std::endl; }

template <typename T> void log(T &&param) { process(std::forward<T>(param)); }

int main(int argc, char *argv[]) {
  Foo x{10};
  log(x);
  log(std::move(x));
}
