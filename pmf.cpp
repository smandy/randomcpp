#include <iostream>

#include <map>

using namespace std;

class A
{
public:
    void foo() { cout << "foo" << endl; }

    void goo() { cout << "goo" << endl; }
};

template <typename T>
class TD;

int main(int argc, char* argv[])
{
    map<string, void (A::*)()> myMap = {{"foo", &A::foo}, {"goo", &A::goo}};
    A a;
    //    myMap["foo"] = &A::foo;
    //    myMap["goo"] = &A::goo;
    (a.*myMap["foo"])();
    (a.*myMap["goo"])();
}
