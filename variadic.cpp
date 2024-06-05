#include <any>
#include <iostream>
#include <tuple>

#include "pretty_printer.hpp"

template <typename... Args>
concept NonVoidArgs = sizeof...(Args) > 0;

template <typename... Args>
concept VoidArgs = sizeof...(Args) == 0;

template <VoidArgs...> constexpr int NumArguments() { return 0; }

template <typename FirstArg, NonVoidArgs... RemainingArgs>
constexpr int NumArguments() {
  return 1 + NumArguments<RemainingArgs...>();
}

template <typename... Ts> struct Process : public Ts... {
  template <typename source, typename H, typename... T>
  auto process(source &&s) {
    // auto x = std::make_tuple(static_cast<Ts&>(*this).call(std::move(s))...);
    if constexpr (NumArguments<T...>() == 0) {
      return static_cast<H>(*this).call(std::move(s));
    } else {
      return process<decltype(static_cast<H>(*this).call(std::move(s))), T...>(
          std::move(static_cast<H>(*this).call(std::move(s))));
    };
  };

  template <typename source> auto call(source &&s) {
    return process<source, Ts...>(std::move(s));
  };
};

struct num {
  int _n;

  num() : _n{} {};

  num(int n) : _n(n) { std::cout << "Num ctor" << n << std::endl; };

  num(const num &x) = delete;
};

std::ostream &operator<<(std::ostream &os, const num &n) {
  std::cout << "num(" << n._n << ")";
  return os;
};

struct Aret : num {};

struct Aparam : num {};

struct Bret : num {};

struct Cret : num {};

struct A {
  Aret call(Aparam &&s) {
    std::cout << "Acall " << s << std::endl;
    return Aret{s._n + 10};
  };
};

struct B {
  Bret call(Aret &&s) {
    std::cout << "Bcall " << s << std::endl;
    return Bret{s._n * 2};
    // return s;
  };
};

struct C {
  Cret call(Bret &&s) {
    std::cout << "Bcall " << s << std::endl;
    return Cret{s._n % 5};
  };
};

int main(int argc, char *argv[]) {
  Process<A, B, C> ab;
  // auto param = Aparam{10};
  auto x = ab.call(Aparam{10});
  std::cout << "Result of process is " << x << std::endl;
  return 0;
}
