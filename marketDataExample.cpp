#include <chrono>
#include <iostream>
#include <thread>

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

// Define the callback function type
typedef function<void(double, double)> MarketDataCallback;

class MarketDataFeed
{
public:
    // Constructor takes a callback function pointer
    MarketDataFeed(std::initializer_list<MarketDataCallback> cbs) : callbacks_(cbs) {}

    // Start the market data feed
    void Start()
    {
        // Simulate market data updates at 10ms intervals
        double bid = 100.0;
        double ask = 101.0;
        while (true) {
            // Update the bid and ask prices
            bid += 0.1;
            ask += 0.1;
            // Call the callback function with the updated prices
            for_each(begin(callbacks_), end(callbacks_), [&](auto& cb) {
                cb(bid, ask);
            });
            // Sleep for 10ms
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

private:
    // Private member variable to store the callback function pointer
    vector<MarketDataCallback> callbacks_;
};

// Define a simple callback function that prints the bid and ask prices
void PrintMarketData(double bid, double ask)
{
    std::cout << "Bid: " << bid << ", Ask: " << ask << std::endl;
}

struct MyCb {
    void operator()(float bid, float ask)
    {
        cout << "Woot " << bid << " " << ask << endl;
    };
};

int main()
{
    MyCb mycb;

    // Create a market data feed object with the callback function
    MarketDataFeed market_data_feed{PrintMarketData, mycb};

    // Start the market data feed
    market_data_feed.Start();

    return 0;
}
