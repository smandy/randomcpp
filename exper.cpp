#include <iostream>

using namespace std;

template <typename T> class TR;

template <typename T> struct Elem { T t; };

template <typename... TS> struct Impl : Elem<TS>... {
  template <typename T> decltype(Elem<T>::t) &get() { return Elem<T>::t; }

  template <typename T> auto get() const { return Elem<T>::t; }
};

int main(int argv, char *argc[]) {
  using ImplType = Impl<int, float>;

  ImplType xs;
  xs.Elem<int>::t = 10;
  xs.Elem<float>::t = 20.0;

  cout << xs.Elem<int>::t << endl;
  cout << xs.Elem<float>::t << endl;

  xs.get<int>() = 20;
  xs.get<float>() = 23.0;

  cout << xs.get<int>() << endl;
  cout << xs.get<float>() << endl;
}
