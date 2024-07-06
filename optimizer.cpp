#include <algorithm>
#include <iostream>

template <typename... T>
struct Optimizer : T... {
    Optimizer() = default;
    explicit Optimizer(T... t) : T(std::move(t))... {}

    template <typename T2>
    auto optimize(int p)
    {
        ((p = static_cast<T&>(*this).optimize(std::move(p))), ...);
        return p;
    }
};

struct Optmizer1 {
    int _x;

    Optmizer1(int x) : _x(x){};

    // template<typename T>
    auto optimize(int node)
    {
        std::cout << "First pass x=" << _x << std::endl;
        // magic 1
        return node + 1;
    }
};

struct Optmizer2 {
    int _x;

    Optmizer2(int x) : _x(x){};

    // template<typename T>
    auto optimize(int node)
    {
        std::cout << "Second pass x=" << _x << std::endl;
        return node * 2;
    }
};

struct Optmizer3 {
    int _x;

    Optmizer3(int x) : _x(x){};

    // template<typename T>
    auto optimize(int node)
    {
        std::cout << "x=" << _x << " Passed " << node << std::endl;
        return node * 2;
    }
};

typedef Optimizer<Optmizer1, Optmizer2, Optmizer3> DefaultOptimizer;

int main()
{
    DefaultOptimizer opt{{10}, {20}, {30}};
    opt.optimize<std::string>(10);
}
