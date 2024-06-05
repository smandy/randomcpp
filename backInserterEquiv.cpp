#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <typename T> void dump(T &xs) {
  std::string sep{""};
  std::cout << "{";
  std::for_each(std::begin(xs), std::end(xs), [&](const auto &x) {
    std::cout << sep << x;
    sep = ",";
  });
  std::cout << "}\n";
}

int main(int, char *[]) {
  std::vector<std::string> myString{"foo", "bar", "baz", "goo", "sue"};
  std::vector<std::string> dest;
  std::vector<std::string> dest2;
  std::vector<std::string> dest3;
  std::vector<std::string> dest4(std::begin(myString), std::end(myString));
  std::vector<std::string> dest5;
  std::vector<std::string> tmp(std::begin(myString), std::end(myString));
  dest5.swap(tmp);
  std::for_each(begin(myString), end(myString),
                [&](auto &x) { dest.push_back(x); });
  std::copy(begin(myString), end(myString), std::back_inserter(dest2));
  for (const auto &x : myString) {
    dest3.push_back(x);
  }
  dump(myString);
  dump(dest);
  dump(dest2);
  dump(dest3);
  dump(dest4);
  dump(dest5);
}
