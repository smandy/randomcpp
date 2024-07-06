#include <future>
#include <iostream>
#include <thread>
#include <tuple>
#include <vector>
// #include <async>

template <typename T>
class TD;

using namespace std;

int doit2() { return 2 + 2; }

template <typename T>
void times(int n, T t)
{
    for (int i = n; i > 0; i--) {
        t();
    }
}

template <typename T>
void doGet(T&& ts)
{
    for (auto& t : ts) {
        cout << t.get() << endl;
    };
}

int main(int argc, char* argv[])
{
    // auto doit = [](){ return 2 + 2; };
    // cout << "foo" << endl;
    // auto x = std::async( doit2 );
    // //TD<std::pair<decltype(doit),decltype(doit2)>> veryCheeky;
    // cout << "bar" << endl;
    // cout << x.get() << endl;
    // cout << "baz" << endl;

    vector<future<int>> myFutures;
    times(10, [&]() { myFutures.emplace_back(std::async(doit2)); });
    myFutures.emplace_back(std::async(doit2));
    for (auto& x : myFutures) {
        cout << x.get() << endl;
    };
    vector<future<int>> myFutures2;
    times(10, [&]() { myFutures2.emplace_back(std::async(doit2)); });
    doGet(myFutures2);
    auto mySync = std::async([]() { return 3; });

    cout << "Woot" << endl;
    times(10, [f = &myFutures2]() { f->emplace_back(std::async(doit2)); });
    doGet(myFutures);

    auto do1 = std::async(doit2);
    // vector<future<int>> myFutures3 { do1 };

    // TD<decltype(mySync)> cheeky;
    // vector<future<int>> myFutures3 { std::move(mySync) };
}
