

#include <complex>
#include <iostream>
#include <ostream>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::complex<T> &t) {
  os << "{" << t.real() << "," << t.imag() << "}";
  return os;
}

int main(int argc, char *argv[]) {
  std::complex<int> x = {2, 3};
  std::complex<int> a = {5, 9};

  auto y = a + 2 * x;
  std::cout << "a is " << a << std::endl;
  std::cout << "x is " << x << std::endl;
  std::cout << "y is " << y << std::endl;
}
