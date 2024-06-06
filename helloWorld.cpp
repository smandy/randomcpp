#include <iostream>

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

// Largely testing out clang-complete + company
using Person = std::pair<std::string, std::string>;

template <typename T, typename Vec=std::vector<T>>
Vec myFilter( Vec &arg, std::function<bool(T&)> pred) {
    Vec ret;
    std::copy_if( arg.begin(), arg.end(), std::back_inserter(ret), pred);
    return ret;
}

int main(int, char *[]) {
    std::cout << "HelloWorld\n";

    std::vector<std::string> strings { "foo", "bar", "baz" };

    std::pair<int, std::string> myPair { 20, "wayhey" };

    std::tuple<int,int,int> Coord;

    std::vector<Person> people = {
        {"Fred", "Flintstone"},
        {"Fred", "Flintstone"},
        {"Barney", "Rubble"} };
    
    for ( const auto &s : strings ) {
        std::cout << "string is - " << s << "\n";
        std::cout << "substr is " << s.substr(2,1)  << "\n";
    };

    std::cout << myPair.first << " " << myPair.second << "\n";

    people.front().first = "Wilma";

    // Woohoo destructuring works
    for( const auto& [first, last] : people ) {
        std::cout << first << " : " << last << "\n";
    };

    std::function<bool(Person&)> pred = [](auto &p) { return p.second == "Flintstone"; };
    for( auto &f : myFilter(people, pred )) {
        std::cout << "A flintstone is " << f.first << " " << f.second << "\n";
    };
}
