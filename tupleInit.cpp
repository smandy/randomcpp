#include <iostream>
#include <tuple>

template <int T> class Foo {
public:
  Foo(int n_) : n(n_) {}
  int n;
};

int main() {
  using MyTup = std::tuple<int, int, int>;
  MyTup t(3, 4, 5);
  int a, b, c;
  std::tie(a, b, c) = t;
  std::cout << "a=" << a << " b=" << b << " c=" << c << std::endl;
}
