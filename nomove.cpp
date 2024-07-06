#include <iostream>

struct A {
    ~A() { std::cout << "I'm melting!" << std::endl; };

    //    A(const A& rhs) = delete;
};

struct B {
    // B(const B& rhs) = delete;
};

A returnA() { return A(); };

B returnB() { return B(); };

int main(int argc, char* argv[])
{
    auto a = returnA();
    auto b = returnB();
    return 0;
}
