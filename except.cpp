#include <exception>
#include <iostream>
#include <string>

class myexc : public std::exception {
public:
  virtual const char *what() const noexcept { return "arse bandit"; };

public:
  virtual ~myexc() {}
};

void foo() {
  std::cout << "I am in foo" << std::endl;
  myexc f;
  throw f;
  std::cout << "I am out of foo" << std::endl;
}

void doit() {
  myexc g;
  throw g;
  foo();
}

int main(int argc, char *argv[]) {
  // doit();

  foo();
}
