#include "tradeClient.h"

#include "trade.h"

struct MyListener {
    template <typename T>
    void call(T&& t)
    {
        std::cout << "Traded " << t << std::endl;
    };
};

int main(int argc, char* argv[])
{
    MyListener l;
    trade_client<MyListener> tc{std::move(l)};
    // tc.listener = &l;
    tc.run();
    std::cout << "All done" << std::endl;
    std::cout << sizeof(Trade) << std::endl;
    return 0;
};
