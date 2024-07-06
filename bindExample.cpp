#include <functional>
#include <iostream>

void f(int a, int b) { std::cout << "a=" << a << " b=" << b << std::endl; };

int main(int argc, char* argv[])
{
    using namespace std::placeholders;

    auto f2 = std::bind(f, 10, _1);

    f2(20);
};
