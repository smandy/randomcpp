#include <iomanip>
#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

struct Foo {
};

std::ostream& operator<<(std::ostream& os, const Foo& foo)
{
    os << "Foo()";
    return os;
};

template <typename T>
struct TD;

// helper type for the visitor #4
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

struct OverLord {
    // template<typename T, typename = std::enable_if_t<std::is_same_v<T, int> >>
    void operator()(int i) { std::cout << " i is " << i << std::endl; }

    // void operator()( int i ) { std::cout << " i is " << i << std::endl; }

    // template<typename T, typename =
    // std::enable_if_t<std::is_same<std::remove_reference<T>,
    // std::string>::value> >
    template <typename T,
              typename = std::enable_if_t<std::is_same_v<T, std::string>>>
    void operator()(T s)
    {
        std::cout << " s is " << s << std::endl;
    }

    // tvoid operator()( std::string s ) { std::cout << " s is " << s <<
    // std::endl; }
};

int main(int argc, char* argv[])
{
    using MyVariant = std::variant<std::string, int>;
    std::vector<MyVariant> xs{"woohoo", 20};

    auto func = overloaded{
        [](std::string&& s) { std::cout << "String is " << s << std::endl; },
        [](int&& x) { std::cout << "int is " << x << std::endl; }};

    // TD<decltype(func)> what_are_you;
    // int x { 21 };
    // std::string s { "woohoo" };
    func(21);
    func("Wooho");

    for (auto& x : xs) {
        std::visit(
            overloaded{
                [](std::string& s) { std::cout << "String is " << s << std::endl; },
                [](int& x) { std::cout << "int is " << x << std::endl; }},
            x);
    };

    auto o = OverLord{};

    o(21);

    int x = 22;
    o(x);

    std::string s{"bazoo"};
    std::string s2{"bazoo"};

    o(std::string{"woohoo"});

    o(s2);

    o(std::move(s));

    return 0;
}
