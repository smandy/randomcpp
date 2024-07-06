#include <functional>
#include <iostream>

using namespace std;

enum class GatewayType { GXA = 0,
                         FIX = 1 };

template <bool cond, typename If, typename Then>
struct select_if {
    using type = Then;
};

template <typename If, typename Then>
struct select_if<true, If, Then> {
    using type = If;
};

template <typename T>
class TD;

// using footype = int(int,int);

void doit(std::function<int(int, int)> f)
{
    cout << "f(2,3) -> " << f(2, 3) << endl;
};

template <typename T>
struct TemplateAdder {
    T operator()(T a, T b) { return a + b; }
};

struct Adder {
    inline int operator()(int a, int b) { return a + b; }
};

function<int(int, int)> makeAdder()
{
    return [](auto x, auto y) { return x * y; };
}

int main(int argc, char* argv[])
{
    using NumericType = select_if<true, int, float>::type;
    NumericType x{};

    cout << " x is " << x << endl;

    doit([](auto a, auto b) {
        cout << "adding " << a << " and " << b << endl;
        return a + b;
    });
    doit([](auto a, auto b) {
        cout << "subtracting " << a << " and " << b << endl;
        return a - b;
    });

    doit(TemplateAdder<int>());

    doit(Adder());

    doit(makeAdder());
}
