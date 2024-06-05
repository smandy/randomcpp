#include <iostream>
#include <vector>

template <typename FunctorType, typename T> void doit(FunctorType &&f, T t) {
  f(t);
}

void printFloat(float f) { std::cout << "Woot" << f << std::endl; }

void printInt(int x) { std::cout << "Poot " << x << std::endl; }

void printFloat2(const float f) { std::cout << "CWoot" << f << std::endl; }

void printInt2(const int x) { std::cout << "Poot " << x << std::endl; };

int main(int, char *[]) {
  float f1{2.0f};
  int i1{2};

  doit(printFloat, f1);
  doit(printInt, i1);
}
