#include <boost/format.hpp>
#include <exception>
#include <iostream>

struct MyException : public std::exception {

  std::string _s;

  MyException(std::string &&s) : _s("MyException: " + s){};
  const char *what() const throw() { return _s.c_str(); };
};

// void grade(int x) noexcept {
// void grade(int x) {
void grade(int x)  {

  if (x > 10)
    throw MyException(boost::str(boost::format("grade is %1%") % x));
};

int main(int argc, char *argv[]) {
  for (int i = 0; i < 20; ++i) {
    try {
      grade(i);
    } catch (MyException &ex) {
      std::cout << "Caught exception: " << ex.what() << std::endl;
      // throw;
    };
  };
}
