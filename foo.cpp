#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // std::cout << "WOot" << std::endl;
    std::vector<std::string> dwarves{"bashful", "doc", "dopey", "grumpy",
                                     "happy", "sleepy", "sneezy"};
    std::for_each(std::begin(dwarves), std::end(dwarves),
                  [](const auto& s) { std::cout << "s is " << s << std::endl; });
}
