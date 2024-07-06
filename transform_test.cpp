#include "pretty_printer.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<uint32_t> ints{1, 3, 5, 7, 9};
    std::vector<uint32_t> squares;
    // squares.resize( ints.size());
    std::transform(std::begin(ints), std::end(ints), std::back_inserter(squares),
                   [=](const auto x) { return x * x; });
    print(std::cout, squares);
    std::cout << std::endl;
}
