#include "iostream"
#include "pretty_printer.hpp"
#include <map>
#include <tuple>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> myInts{1, 2, 3};
  print_line(std::cout, myInts);
  std::vector<std::pair<int, int>> myPairs2{{1, 2}, {3, 4}};
  std::cout << "Going for it"
            << "\n";
  print_line(std::cout, myPairs2);
  std::cout << "Went for it"
            << "\n";

  std::map<int, std::vector<std::string>> myStuff;

  myStuff[0].push_back("andy");
  myStuff[0].push_back("pandy");
  myStuff[0].push_back("dandy");

  myStuff[1].push_back("foo");
  myStuff[1].push_back("bar");
  myStuff[1].push_back("baz");

  myStuff[2].push_back("red");
  myStuff[2].push_back("green");
  myStuff[2].push_back("blue");

  print_line(std::cout, myStuff);
}
