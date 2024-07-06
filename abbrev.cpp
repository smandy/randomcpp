#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int, char*[])
{
    vector<int> xs{1, 2, 2, 3};
    for_each(begin(xs), end(xs), [](auto& s) { cout << s << endl; });

    auto pos = std::adjacent_find(std::begin(xs), std::end(xs));
    if (pos != std::end(xs)) {
        std::cout << "pos is " << *pos << std::endl;
    }
}
