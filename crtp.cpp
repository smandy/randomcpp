#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Base {
public:
  inline T &instance() { return *static_cast<T>(this); }

  void doit() { instance().doit(); }
};

class A : public Base<A> {
public:
  void doit() { cout << "Woot! a" << endl; }
};

class B : public Base<B> {
public:
  void doit() { cout << "Woot! b" << endl; }
};

int main(int argc, char *argv[]) {
  A a;
  B b;
  vector<int> ints{1, 2, 3, 4, 5};

  // size_t mySize = ints.size();

  a.doit();
  b.doit();

  std::cout << "Woot" << std::endl;
}
