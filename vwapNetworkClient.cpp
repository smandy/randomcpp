// #include "process.hpp"

#include "tim_process.hpp"

#include "trade.h"
#include "tradeClient.h"

struct vwap {
    int qty;
    float volume;

    vwap() : qty{}, volume{} {};

    float call(Trade&& trade)
    {
        qty += 1;
        volume += (trade.bid + trade.ask) / 2.0;
        return get();
    };

    float get() { return qty == 0 ? 0.0 : volume / qty; };
};

struct dumper {
    float call(float f)
    {
        std::cout << f << std::endl;
        return f;
    };
};

struct doubler {
    float call(float f) { return 2.0 * f; };
};

// struct Forwarder {
//     Forwarder() {};
//     Forwarder(Forwarder&&) = default;
//   Trade &&call(Trade &&trade) {
//       std::cout << trade << std::endl;
//       return std::move(trade);
//   };
// };

typedef Process<vwap, dumper, doubler> myProcess;
struct Forwarder {
    myProcess* p;
    template <typename T>
    void call(T t)
    {
        p->call<Trade>(std::move(t));
        std::cout << "Called with trade " << t << std::endl;
    };
};

int main(int argc, char* argv[])
{
    Forwarder f;
    myProcess p{{}, {}, {}};
    f.p = &p;
    trade_client<Forwarder> tc{std::move(f)};
    tc.run();
}
