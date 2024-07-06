#include <bits/stdc++.h>

using namespace std;
template <class... Ts>
struct sink : std::function<void(Ts...)> {
    using std::function<void(Ts...)>::function;
};
template <class... Ts>
using source = sink<sink<Ts...>>;
template <class In, class Out>
using process = sink<source<In>, sink<Out>>;
template <class In, class Out>
sink<In> operator|(process<In, Out> a, sink<Out> b)
{
    return [a, b](In in) {
        a([&in](sink<In> s) mutable { s(std::forward<In>(in)); }, b);
    };
}
template <class In, class Out>
source<Out> operator|(source<In> a, process<In, Out> b)
{
    return [a, b](sink<Out> out) { b(a, out); };
}

template <class In, class Mid, class Out>
process<In, Out> operator|(process<In, Mid> a, process<Mid, Out> b)
{
    return [a, b](source<In> in, sink<Out> out) {
        a(in, b | out); // or b( in|a, out )
    };
}
template <class... Ts>
sink<> operator|(source<Ts...> a, sink<Ts...> b)
{
    return [a, b] { a(b); };
}
process<char, char> to_upper = [](source<char> in, sink<char> out) {
    in([&out](char c) { out(std::toupper(c)); });
};
process<char, char> with_new_line = [](source<char> in, sink<char> out) {
    in([&out](char c) {
        out(c);
        out('\n');
    });
};
source<char> hello_world = [ptr = "hello world"](sink<char> s) {
    for (auto it = ptr; *it; ++it) {
        s(*it);
    }
};

sink<char> doprint = [](char c) { std::cout << c; };

template <typename T>
struct TD;

int main()
{
    auto prog = hello_world | to_upper | with_new_line | doprint;
    prog();

    // TD<decltype(hello_world)> hw;

    // TD<decltype(print)> p;
    /*string s="hello world";
    for(auto&c:s){
      auto out=std::toupper(c);string t;t.push_back(out);
      cout<<t<<'\n';
    }*/
}
