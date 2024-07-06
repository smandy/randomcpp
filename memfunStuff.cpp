#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template <typename T, typename R, typename... Args>
struct memfun {
    using MemFun = R (T::*)(Args...);

    MemFun mfn;

    memfun(MemFun _mfn) : mfn(_mfn) {}

    void operator()(T& handle, Args... xs) { (handle.*mfn)(xs...); }
};

template <typename T, typename R, typename... Args>
struct wrapper : std::function<R(Args...)> {
    using MemFun = R (T::*)(Args...);

    MemFun mfn;
    T& ref;

    wrapper(T _ref, MemFun _mfn) : ref(_ref), mfn(_mfn) {}

    void operator()(Args... xs) { (ref.*mfn)(xs...); }
};

template <typename T, typename R, typename... Args>
memfun<T, R, Args...> makeMemFun(R (T::*p)(Args...))
{
    return memfun<T, R, Args...>(p);
}

template <typename T, typename R, typename... Args>
wrapper<T, R, Args...> wrapMemFun(T& ref, R (T::*p)(Args...))
{
    return wrapper<T, R, Args...>(ref, p);
}

struct Foo {
    const std::string s;

    Foo(const std::string& _s) : s(_s) {}

    void bar(const std::string& s) { std::cout << "s " << s << std::endl; }
};

int main(int argc, char* argv[])
{
    Foo f("woot");
    auto x = makeMemFun(&Foo::bar);
    x(f, "woot");
    auto wrapper = wrapMemFun(f, &Foo::bar);
    wrapper("Woot");

    auto myvec = std::vector<std::string>{"foo", "bar", "baz"};
    std::for_each(begin(myvec), end(myvec), wrapMemFun(f, &Foo::bar));
}
