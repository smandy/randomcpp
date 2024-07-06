#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void make_thread(string& s) { cout << "Woohoo " << s << endl; };

struct wrapper {
    wrapper() = delete;
    void operator=(const wrapper&) = delete;

    wrapper(wrapper&& rhs) : s(std::move(rhs.s))
    {
        cout << "Move ctor " << rhs.s << endl;
    }

    wrapper& operator=(wrapper&& rhs)
    {
        cout << "Move assignment of " << rhs.s << endl;
        s = std::move(rhs.s);
        return *this;
    }

    wrapper(string s_) : s(s_) {}

    ~wrapper() { cout << s << " is melting" << endl; }

    string s;

    void run() { cout << "running " << s << endl; }
};

void make_threads(vector<wrapper>& wrappers, vector<thread>& threads)
{
    vector<thread> ret;
    for_each(wrappers.begin(), wrappers.end(), [&ret](wrapper& w) {
        ret.push_back(thread(&wrapper::run, std::ref(w)));
    });
    ret.swap(threads);
}

int main(int, char*[])
{
    vector<string> myVec{"bashful", "doc", "dopey", "grumpy",
                         "happy", "sleepy", "sneezy"};
    for (auto& s : myVec) {
        std::transform(
            s.begin(), s.end(), s.begin(),
            [](unsigned char c) -> unsigned char { return std::toupper(c); });
    }

    for (auto& x : myVec) {
        std::cout << x << std::endl;
    }

    vector<string> names{"bashful", "doc", "dopey", "grumpy",
                         "happy", "sleepy", "sneezy"};
    vector<wrapper> wrappers;
    wrappers.reserve(names.size());
    // threads.reserve(names.size())
    cout << "Create wrappers " << endl;
    std::transform(names.begin(), names.end(), back_inserter(wrappers),
                   [](string& s) {
                       cout << "Creating " << s << endl;
                       return wrapper(s);
                   });
    vector<std::thread> threads;
    make_threads(wrappers, threads);
    for (auto& t : threads) {
        t.join();
    }
}
