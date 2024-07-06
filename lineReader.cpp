#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[])
{
    std::ifstream is("/home/andy/flight.txt", std::ios::in);
    std::vector<std::string> myLines{std::istream_iterator<std::string>{is},
                                     std::istream_iterator<std::string>{}};
    for (auto& s : myLines) {
        std::cout << "Have a line " << s << std::endl;
    }
}
