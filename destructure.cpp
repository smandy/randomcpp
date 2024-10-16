#include <iostream>
#include <string>
#include <tuple>

// using Tup = std::tuple<int, std::string>;

auto return_tuple() { return std::make_tuple(21, "foo"); };

int main()
{
    auto [a, b] = return_tuple();
    std::cout << " a=" << a << " b=" << b << std::endl;
};
