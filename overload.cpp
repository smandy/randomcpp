#include <iostream>

// int doit(int x, int y) {
//     return x + y;
// }

template <typename F> struct TR;

auto doit(int x, float y) { return x + y; }

// TR<decltype(doit(2, 3))> myFailure;

int main(int argc, char *argv[]) { std::cout << doit(2, 3) << std::endl; }
