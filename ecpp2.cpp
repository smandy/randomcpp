#include "pretty_printer.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Remove third element from vector!

template <typename Iter>
Iter remove(Iter first, Iter last, size_t n)
{
    assert(std::distance(first, last) >= n);
    advance(first, n);
    if (first != last) {
        auto dest = first;
        return copy(++first, last, dest);
    };
    return last;
}

int main(int argc, char* argv[])
{
    std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<int> myVec2(begin(myVec), end(myVec));

    print_line(std::cout, myVec);
    myVec.erase(remove(begin(myVec), end(myVec), 3), end(myVec));
    print_line(std::cout, myVec);
    // std::vector<int> myVec { 1,2,3,4,5,6,7,8,9,10};
    print_line(std::cout, myVec2);

    myVec2.erase(std::remove_if(begin(myVec2), end(myVec2),
                                [](const auto& x) { return x % 2 == 0; }),
                 end(myVec2));
    print_line(std::cout, myVec2);
}
