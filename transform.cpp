#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename... Args, template <class...> class Container>
void pp(T& os, Container<Args...>& ts)
{
    string sep = "";
    os << "[";
    for (auto& t : ts) {
        os << sep;
        os << t;
        sep = ", ";
    }
    os << "]";
}

template <typename T, typename... Args>
T& operator<<(T& os, vector<Args...>& ts)
{
    pp(os, ts);
    return os;
}

template <int x>
inline int const myAdd(int y) { return x + y; };

int main(int argc, char* argv[])
{
    vector<int> x{1, 2, 3, 4, 5, 6, 7};
    vector<int> y(x.size());
    auto square = [=](auto x) { return x * x; };
    transform(begin(x), end(x), begin(y), square);
    transform(begin(x), end(x), begin(x), myAdd<30>);
    cout << x << " foo " << y << " bar " << endl;
};
