#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

template <typename T> struct TR;

int main(int argc, char *argv[]) {
  std::map<std::string, int> myMap{{"foo", 2}, {"goo", 3}, {"baz", 24}};
  std::for_each(std::begin(myMap), std::end(myMap), [&](const auto &x) {
    std::cout << "first=" << x.first << " second=" << x.second << std::endl;
  });
  using person = std::tuple<std::string, std::string, int>;
  std::vector<person> people = {{"Andy", "Smith", 45}, {"Sophie", "Hind", 16}};
  std::for_each(std::begin(people), std::end(people), [](const auto &x) {
    std::cout << "a = " << std::get<0>(x) << " b=" << std::get<1>(x)
              << " c=" << std::get<2>(x) << std::endl;
  });
}
