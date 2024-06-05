#include <iostream>
#include <ostream>

#include <algorithm>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <vector>

//using namespace std;

template <typename T> struct Counter {
  T x;
  Counter() : x(){};
  void operator()(const T &t) { x += t; };
};

template <typename T> class TR;

using BinFunc = std::function<int(int, int)>;
using SPM = std::vector<std::pair<std::string, BinFunc>>;

template <typename T> inline std::ostream &operator<<(std::ostream &os, Counter<T> &c) {
  os << "Counter(" << c.x << ")";
  return os;
}

struct Adder {
  inline int operator()(int a, int b) { return a + b; }
};

struct Adder2 {
  inline int add(int a, int b) { return a + b; }
};

struct Adder3 {
  static inline int add(int a, int b) { return a + b; }
};

int main(int argc, char *argv[]) {
  // using thaip = double;
  // vector<thaip> myInts { 1,2,3,4,5, 6.5};
  //  using CT = Counter<thaip>;
  //  auto x = for_each(begin(myInts), end(myInts), CT());
  //  cout << x << endl;
  auto ad2 = Adder2();
  using namespace std::placeholders;
  auto addCall = std::bind(&Adder2::add, &ad2, _1, _2);
  SPM dispatch = {
      {"+", [](int x, int y) { return x + y; }},
      {"+", Adder()},
      {"+", addCall},
      {"+", &Adder3::add},
      {"*", [](int x, int y) { return x * y; }},
      {"-", [](int x, int y) { return x - y; }},
      {"%", [](int x, int y) { return x % y; }},
      {"/", [](int x, int y) { return x / y; }},
  };
std::vector<std::pair<int, int>> inputs = {{1, 2}, {3, 4}, {5, 6}};
  {
    int x, y;
    std::string desc;
    BinFunc functor;
    for (auto &p : inputs) {
        std::tie(x, y) = p;
      for (auto &spf : dispatch) {
        tie(desc, functor) = spf;
        std::cout << x << " " << desc << " " << y << " = " << functor(x, y) << std::endl;
      }
    }
  }
  std::cout << std::equal_to<int>()(1, 1) << std::endl;
  auto eq5 = std::bind(std::equal_to<int>(), _1, 5);
  
  for (auto &x : {1, 2, 3, 4, 5, 6, 7}) {
      std::cout << x << " -> " << eq5(x) << std::endl;
  }
}
