#include <iostream>
#include <string>
#include <vector>

int main(int, char *[]) {
  std::vector<std::string> names = {"foo", "bar", "baz"};
  auto sep = "";
  std::cout << "{";
  for (auto &s : names) {
    std::cout << sep;
    std::cout << s;
    sep = ", ";
  };
  std::cout << "}";
  std::cout << "\n";
}
