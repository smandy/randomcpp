#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<uint8_t> vec(10);
    std::cout << "Size is " << std::to_string(vec.size()) << std::endl;
}
