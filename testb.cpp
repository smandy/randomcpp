#include "bpointer.hpp"

struct Foo {
    void wayhey() { std::cout << "Wayhey!!" << std::endl; };

    Foo() { std::cout << "Foo ctor" << std::endl; };

    ~Foo() { std::cout << "Foo dtor" << std::endl; }
};

int main(int argc, char* argv[])
{
    using bfoo = bpointer<Foo>;
    bfoo x(new Foo());
    std::cout << "Create y from z" << std::endl;
    bfoo y(x);
    std::cout << "Default init z" << std::endl;
    bfoo z;
    std::cout << "Assign z to x" << std::endl;
    z = x;

    x->wayhey();
    y->wayhey();
    z->wayhey();
}
