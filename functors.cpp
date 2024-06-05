#include <functional>
#include <iostream>

using namespace std::placeholders;

void call(std::function<void()> x) { x(); }

void add(int x, int y) { std::cout << "Add " << x << " " << y << std::endl; }

int main(int argc, char *argv[]) {
  auto x = std::bind(add, 2, 3);

  auto x2 = std::bind(add, 5, _1);
  auto x3 = std::bind(x2, 10);

  call(x);
  call(x3);
}
