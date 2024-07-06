#include <iostream>
#include <tuple>

using namespace std;

int main(int argc, char* argv[])
{
    tuple<int, float> myTup{23, 45.2f};
    cout << get<0>(myTup) << " " << get<1>(myTup) << endl;

    int a;
    float b;
    tie(a, b) = myTup;
    cout << a << " " << b << endl;
    auto myTup2 = make_tuple<int, float, bool>(10, 20.0f, true);
    cout << get<0>(myTup2) << " " << get<1>(myTup2) << " " << get<2>(myTup2)
         << endl;
}
