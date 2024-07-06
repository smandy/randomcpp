#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

// Pretty print stuff for diagnostics
// template< typename T>
// void pp( T &t ) {
//     std::std::cout << t;
// };

template <typename T, typename U>
void pp(pair<T, U>& t)
{
    std::cout << "{" << t.first << "," << t.second << "}";
}

template <typename T>
void pp(T& t) { std::cout << t << std::endl; }

template <typename... Args, template <class...> class Container>
void pp(Container<Args...> ts)
{
    string sep = "";
    std::cout << "[";
    for (auto t : ts) {
        std::cout << sep;
        pp(t);
        sep = ", ";
    };
    std::cout << "]";
}

std::vector<int> const makeVec(int n)
{
    vector<int> ret;
    for (int i = 0; i < n; ++i) {
        ret.push_back(i);
    };
    return ret;
}

int main(int argc, char* argv[])
{
    vector<int> myVec = makeVec(10);
    for (int i = 0; i < 10; ++i) {
        std::cout << myVec[i] << std::endl;
    };
    myVec[5] = 3;
    vector<int> vec2(begin(myVec), end(myVec));

    pp(vec2);
}
