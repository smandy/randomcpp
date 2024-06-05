#include <iostream>
#include <vector>

template <typename U, typename T> auto transform3(std::vector<T> xs) {
  T t;
  using V = decltype(U::invoke(t));
  std::vector<V> ret;
  for (auto &x : xs) {
    ret.push_back(U::invoke(x));
  };
  return ret;
};

struct Transform {
  static int invoke(int x) { return x * x; };
};

struct Negate {
  static int invoke(int x) { return -x; };
};

int main(int argc, char *argv[]) {
  std::vector<int> myInts = {1, 2, 3};
  auto ys = transform3<Transform>(myInts);
  for (auto &y : ys) {
    std::cout << y << std::endl;
  };

  auto zz = transform3<Negate>(myInts);
  for (auto &y : zz) {
    std::cout << y << std::endl;
  };
};
