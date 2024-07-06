#include <iostream>
#include <string>

template <typename C, template <typename> typename B>
struct AImpl {
    B<C> b;

    AImpl() : b{} { std::cout << "A Impl" << std::endl; };

    void run()
    {
        std::cout << "Run" << std::endl;
        for (int i = 0; i < 100; ++i) {
            std::cout << "A ticking " << i << std::endl;
            b.tick(i);
        };
    };
};

template <typename C>
struct BImpl {
    void tick(int i)
    {
        std::cout << "B ticking " << i << std::endl;
        c.tick(i);
    };

    BImpl() : c{} { std::cout << "B impl" << std::endl; };

    C c;
};

struct CImpl {
    CImpl() { std::cout << "C impl" << std::endl; }

    void tick(int i) { std::cout << "C ticking " << i << std::endl; };
};

template <typename C, template <typename> typename B,
          template <typename, template <typename> typename> typename A>
struct Config;

template <typename C, template <typename> typename B,
          template <typename, template <typename> typename> typename A>
class System
{
    typedef A<C, B> SystemType;
    // typedef SystemType::Config ConfigType;
    typedef Config<C, B, A> ConfigType;

public:
    System(ConfigType& ac){};

    SystemType a;

    void run() { a.run(); };
};

template <>
struct Config<CImpl, BImpl, AImpl> {
    int port;
};

int main(int argc, char* argv[])
{
    using MySys = System<CImpl, BImpl, AImpl>;
    using ConfigType = Config<CImpl, BImpl, AImpl>;

    // system(ConfigType * config) {

    ConfigType config{1066};
    MySys system(config);

    system.run();

    return 0;
}
