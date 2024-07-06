#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> my_strings{"foo", "bar", "baz", "goo"};

    std::for_each(std::begin(my_strings), std::end(my_strings),
                  [](const auto& x) {
                      static char sep = '[';
                      std::cout << sep;
                      std::cout << x;
                      sep = ',';
                  });
    std::cout << "]";
}
