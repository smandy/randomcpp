#include "pretty_printer.hpp"
#include <iostream>
#include <iterator>
#include <vector>

template <typename B, typename D> class IsDerivedFrom {
  class No {};
  class Yes {
    No nos[2];
  };

  static Yes test(B *);
  static No test(...);

public:
  enum { Is = sizeof(test(static_cast<D *>(0))) == sizeof(Yes) };
};

class Base {};
class Derived : public Base {};
class UnDerived {};

template <typename T> struct Clonable { T Clone(); };

class ClonableFoo : public Clonable<ClonableFoo> {
public:
  ClonableFoo Clone() {
    std::cout << "ClonableFoo clone invoked" << std::endl;
    return ClonableFoo();
  }
};

class CheekyFoo : public Clonable<CheekyFoo> {
public:
  CheekyFoo Clone() { return CheekyFoo(); }
};

class NonClonableFoo {
public:
  NonClonableFoo() { std::cout << "NonClonableFoo default ctor" << std::endl; }

  NonClonableFoo(const NonClonableFoo &x) {
    std::cout << "NonClonableFoo copy ctor invoked!" << std::endl;
  }
};

template <typename T, int x> struct cloneImpl { static T clone(T &t); };

template <typename T> struct cloneImpl<T, 1> {
  static T clone(T &t) {
    std::cout << "Cloningclone invoked" << std::endl;
    return t.Clone();
  }
};

template <typename T> struct cloneImpl<T, 0> {
  static T clone(T &t) {
    std::cout << "CopyingClone invoked " << std::endl;
    T ret(t);
    return ret;
  }
};

template <typename T> T clone(T &t) {
  return cloneImpl<T, IsDerivedFrom<Clonable<T>, T>::Is>::clone(t);
}

int main(int argc, char *argv[]) {
  std::cout << IsDerivedFrom<Base, Derived>::Is << std::endl;
  std::cout << IsDerivedFrom<Base, UnDerived>::Is << std::endl;
  std::cout << "Answer is "
            << IsDerivedFrom<Clonable<ClonableFoo>, ClonableFoo>::Is
            << std::endl;

  ClonableFoo cf;
  NonClonableFoo ncf;
  CheekyFoo kf;

  clone(cf);
  clone(ncf);
  clone(kf);
}
