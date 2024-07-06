#include <future>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>

int _fib(int n)
{
    if (n < 3) {
        return 1;
    } else {
        return _fib(n - 1) + _fib(n - 2);
    };
}

std::tuple<int, int> fib(int n)
{
    // cout << "Starting " << n << endl;
    auto ret = _fib(n);
    // cout << "Ending   " << n << " -> " << ret << endl;
    return std::make_tuple(n, ret);
}

// template<typename T>
// class TD;

int main(int, char*[])
{
    std::vector<std::future<decltype(fib(0))>> myFuts;
    std::vector<std::future<int>> myInts;

    for (int x : {20, 35, 30, 40, 41, 42, 43, 44, 45}) {
        myFuts.push_back(std::move(std::async(std::launch::async, &fib, x)));
    }

    int n, r;
    for (auto& x : myFuts) {
        std::tie(n, r) = x.get();
        std::cout << n << " -> " << r << std::endl;
    };

    for (int x = 0; x < 20; x++) {
        myInts.push_back(std::move(std::async(std::launch::async, [=]() { return x + 10; })));
    };

    for (auto& x : myInts) {
        std::cout << x.get() << std::endl;
    }
}
