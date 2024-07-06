#include <iostream>

int main(int argc, char* argv[])
{
    struct m1 {
        // melter() { std::cout << "Im begining\n"; };

        ~m1() { std::cout << "Im melting!!\n"; };
    } m;

    struct m2 {
        // melter() { std::cout << "Im begining\n"; };

        ~m2() { std::cout << "Im melting2!!\n"; };
    } m2;

    std::cout << "Beginngin " << std::endl;

    return 0;
}
