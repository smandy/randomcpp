#include <iostream>
#include <tuple>

template <typename T>
void bar(T&& t)
{
    std::cout << "Bar called with " << t << std::endl;
}

// Scott myers introspection hack
template <typename T>
class TD;

template <typename... Args>
void callBar(Args&&... args)
{
    // From
    // http://stackoverflow.com/questions/25680461/variadic-template-pack-expansion
    auto ign = {((void)bar(std::forward<Args>(args)), 0)...};

    // TD<decltype(ign)> ignType;

    // for ( auto&x : dummy) {
    //     std::cout << "Dummmy has " << x << std::endl;
    // };

    // Should work in 17 - fold expressions. Pretty cool
    //(..., bar(std::forward<Args>(args)) );
};

int main(int argc, char* argv[]) { callBar(1, 2, 3, "foo", 10, 12, 13); }
