#include <string>
#include <vector>

#include "pretty_printer.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  vector<string> orig{"foo", "bar", "baz"};

  vector<string> new2(orig);

  std::cout << "Orig";
  print_line(std::cout, orig);
  std::cout << std::endl;

  std::cout << "New2";
  print_line(std::cout, new2);
  std::cout << std::endl;

  vector<string> newVec(std::move(orig));

  std::cout << "Orig";
  print_line(std::cout, orig);
  std::cout << std::endl;

  std::cout << "New";
  print_line(std::cout, newVec);
  std::cout << std::endl;
};
