#include <algorithm>
#include <iostream>
#include <vector>

int main()
{

    std::vector<int> xs{1, 2, 3, 3, 3, 4, 5, 6, 7};

    auto res = std::equal_range(std::begin(xs), std::end(xs), 3, [=](auto& x, auto& y) { return x < y; });

    std::for_each(res.first, res.second, [](const auto& x) { std::cout << "I have " << x << std::endl; });
};
