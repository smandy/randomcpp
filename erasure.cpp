#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename... Args, template <class...> class Container>
void pp(Container<Args...>& ts)
{
    std::string sep = "";
    std::cout << "[";
    for (auto& t : ts) {
        std::cout << sep;
        std::cout << t;
        sep = ", ";
    }
    std::cout << "]";
}

int main(int argc, char* argv[])
{
    std::vector<int> myVec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    myVec.erase(std::remove_if(begin(myVec), end(myVec),
                               [](auto& x) { return x % 2 == 0; }),
                end(myVec));
    pp(myVec);
    std::cout << std::endl;
}
