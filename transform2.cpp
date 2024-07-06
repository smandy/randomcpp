#include <algorithm>
#include <iostream>
#include <vector>

#include "pretty_printer.hpp"
#include "sepInserter.hpp"

int main(int, char*[])
{
    std::vector<int> firsts = {1, 2, 3, 4, 5};
    std::vector<int> seconds = {10, 2, 10, 30, 10, 3, 2, 10};
    // std::vector<int> seconds = { 10, 2, 10 };

    std::vector<int> dest;
    std::transform(begin(firsts), end(firsts), begin(seconds),
                   std::back_inserter(dest), [](int x, int y) { return x * y; });

    std::cout << "{";
    std::copy(begin(dest), end(dest), SepInserter<int>(std::cout));
    std::cout << "}" << std::endl;
    print_line(std::cout, seconds);
    std::for_each(begin(seconds), end(seconds), [](auto& x) { x *= 2; });
    print_line(std::cout, seconds);
}
