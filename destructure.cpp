#include <iostream>
#include <tuple>

// using Tup = std::tuple<int, std::string>;

auto return_tuple() { return std::make_tuple(21, "foo"); };

struct S {
    int x;
    int y;
};

int main()
{
    auto [a, b] = return_tuple();
    std::cout << " a=" << a << " b=" << b << std::endl;

    S s{3, 4};

    auto [c, d] = s;

    std::cout << "c is " << c << " d is " << d << "\n";
};
