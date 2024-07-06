#include <iostream>

class Experiment
{
public:
    const std::string& s;
    Experiment(const std::string _s) : s(_s)
    {
        std::cout << "s is " << &s << " _s is " << &_s << std::endl;
    }
};

Experiment create() { return Experiment("Woot"); }

int main(int, char*[])
{
    auto x = create();
    std::cout << x.s << std::endl;
    std::cout << "&x.s is " << &x.s << std::endl;
}
