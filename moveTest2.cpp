#include <initializer_list>
#include <iostream>

using namespace std;

struct Foo {
  Foo() = default;

  Foo(const Foo &) = delete;
};

template <typename T> struct Foo2 {
  Foo2(std::initializer_list<T> ts) {
    for (const T &t : ts) {
      cout << "Woot! I have a " << t << endl;
    }
  }
};

int main(int argc, char *argv[]) {
  Foo foo1;
  //  Foo foo2 = foo1;
  Foo2<int> my2 = {1, 2, 3};
}
