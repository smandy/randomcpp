#include <iostream>

struct Foo {
  const std::string myString;

  Foo(const std::string &s) : myString(s){};
};

Foo makeFoo() {
  std::string s = "Hello there";
  Foo ret(s);
  return ret;
}

int main(int argc, char *argv[]) {
  auto x = makeFoo();
  std::cout << x.myString << std::endl;
}
