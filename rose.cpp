#include <iostream>

class Rose {};

class A {
public:
  typedef Rose rose;
};

template <typename T> class B : public T {
public:
  typedef typename T::rose foo;
};

template <typename T> void smell(T) { std::cout << "Aweful" << std::endl; }

void smell(Rose) { std::cout << "Sweet" << std::endl; }

int main() {
  smell(A::rose());
  smell(B<A>::foo());
}
