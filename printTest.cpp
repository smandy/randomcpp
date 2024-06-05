#include "pretty_printer.hpp"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<char> myVec{'a', 'r', 's', 'e', ' ', 'b',
                          'a', 'n', 'd', 'i', 't'};
  print(std::cout, myVec);
  std::cout << std::endl;
}
