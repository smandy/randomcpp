#include <iostream>
#include <map>
#include <vector>

#include <boost/asio.hpp>

using namespace std;

template <typename T>
class Gateway
{
public:
    inline auto instance() { return *static_cast<T*>(this); }

    int trade() { return instance().trade(); }
};

template <typename T, typename OrderType>
class RiskCheck
{
    inline auto instance() { return *static_cast<T*>(this); }

public:
    bool allow(OrderType meta) { return instance().allow(meta); }
};

template <typename T, bool x>
class ConstRiskCheck : public RiskCheck<ConstRiskCheck<T, x>, T>
{
public:
    bool allow(T t) { return x; }
};

class AllowZ : public RiskCheck<AllowZ, std::string>
{
public:
    bool allow(std::string s) { return s[0] == 'Z'; }
};

template <typename T>
class MD
{
public:
    inline auto instance() { return *static_cast<T*>(this); }

    int tick() { return instance().tick(); }
};

class TwoMD : public MD<TwoMD>
{
public:
    int tick() { return 2; }
};

class ThreeGW : public Gateway<ThreeGW>
{
public:
    int trade() { return 3; }
};

template <int N>
class NGW : public Gateway<NGW<N>>
{
public:
    int trade() { return N; }
};

template <int N>
class NMD : public MD<NMD<N>>
{
public:
    int tick() { return N; }
};

template <typename MDType, typename GatewayType, typename RiskCheckType,
          typename OrderType>
class System : public MD<MDType>,
               public Gateway<GatewayType>,
               public RiskCheck<RiskCheckType, OrderType>
{
    using MD<MDType>::tick;
    using Gateway<GatewayType>::trade;
    using RiskCheck<RiskCheckType, OrderType>::allow;

public:
    inline int act(OrderType s)
    {
        if (allow(s)) {
            auto t = tick();
            auto t2 = trade();
            // cout <<  t << " " << t2 << endl;
            return t * t2;
        } else {
            return 0;
        };
    }
};

struct Foo {
    int doit() { return 2; }

    int doitagain() { return 10; }

    int anotherOne() { return 12; }
};

int main(int argc, char* argv[])
{
    using SystemType = System<TwoMD, ThreeGW, AllowZ, std::string>;
    using System34 = System<NMD<10>, NGW<3>, AllowZ, std::string>;
    using DenySixSeven =
        System<NMD<6>, NGW<7>, ConstRiskCheck<std::string, false>, std::string>;
    using AllowSixSeven =
        System<NMD<6>, NGW<7>, ConstRiskCheck<std::string, true>, std::string>;

    SystemType s;
    System34 s2;
    DenySixSeven dss;
    AllowSixSeven ass;

    cout << "s(foo) " << s.act("foo") << endl;
    cout << "s(Zoo) " << s.act("Zoo") << endl;

    cout << "s2(goo) " << s2.act("goo") << endl;
    cout << "s2(Zar) " << s2.act("Zar") << endl;

    cout << "dss(Woot) " << dss.act("Woot") << endl;
    cout << "ass(Woot) " << ass.act("Woot") << endl;

    std::string myString;
    Foo myFoo;
    myFoo.doit();

    std::cout << "This stuff actually works!!!" << std::endl;
    std::map<int, double> myMap;
}
