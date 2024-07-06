#include "threadpool.h"
#include <iostream>

int square(int n)
{
    return n * n;
};

int main()
{
    ThreadPool pool(4);
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    std::cout << result.get() << std::endl; // prints 42
    auto result2 = pool.enqueue([]() { return square(2); });
    std::cout << result2.get() << std::endl;

    return 0;
}
