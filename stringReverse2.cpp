#include <algorithm>
#include <iostream>

int main(int argc, char *argv[]) {
  std::string s{"amanaplanacanalpanama"};
  std::string s2{s};
  std::reverse(std::begin(s2), std::end(s2));
  std::cout << s << std::endl;
  std::cout << s2 << std::endl;
}
