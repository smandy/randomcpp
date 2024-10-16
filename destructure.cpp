#include <iostream>
#include <string>
#include <tuple>
// using Tup = std::tuple<int, std::string>;

auto return_tuple() { return std::make_tuple(21, "foo"); };

struct S {
    const uint32_t x;
    const uint32_t y;
    const std::string foo;
};

int main()
{
    auto [a, b] = return_tuple();
    std::cout << " a=" << a << " b=" << b << std::endl;

    S s{3, 4, "banana"};
    const auto [c, d, s2] = s;
    std::cout << "c is " << c << " d is " << d << " foo is " << s2 << "\n";
};
