#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> xs{"foo", "bar", "baz"};
    std::for_each(std::begin(xs), std::end(xs), [&](const auto& s) {
        std::cout << "x is " << s << std::endl;
    });
}
