#include <iostream>
#include <string>
#include <tuple>

using Tup = std::tuple<int, std::string>;

Tup return_tuple() { return Tup(21, "foo"); };

int main() {
  auto [a, b] = return_tuple();
  std::cout << " a=" << a << " b=" << b << std::endl;
};
