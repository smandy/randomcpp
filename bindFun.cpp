
#include <functional>
#include <iostream>

struct Foo {
  void doSomething(std::string s) { std::cout << "S is " << s << "\n"; }

  void doSomethingElse(int x) { std::cout << "n is " << x << "\n"; }
};

using StringMember = std::function<void(std::string)>;

template <typename T> struct TD;

int main(int argc, char *argv[]) {
  Foo f;
  f.doSomething("hello");
  auto x = [&f](std::string s) { f.doSomething(s); };
  // TD<decltype(x)> aType;
  x("Woot");
}
