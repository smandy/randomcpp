#include <iostream>
#include <vector>

template <typename... Args>
void acceptInitList(Args&&... args)
{
    // std::cout << "Got args " << args << std::endl;
    std::vector<int> myVec(args...);
    for (auto& x : myVec) {
        std::cout << x << std::endl;
    }
}

template <typename T>
class TD;

int main(int argc, char* argv[])
{
    auto x = {1, 2, 3, 4, 5};
    // TD<decltype(x)> myX;
    acceptInitList(x);
}
