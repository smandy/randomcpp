#include "rateTimer.h"

#include <iostream>
using namespace std;

RateTimer::RateTimer()
    : lastTime(hrc::now()), lastTicks{}, resolution{MyDuration(1).count()},
      durToSecs((std::chrono::seconds(1) / MyDuration(1)))
{
    cout << "DurSecs is " << durToSecs << endl;
};

double RateTimer::rateForTicks(uint64_t newTicks)
{
    const auto newTime = hrc::now();
    auto durSecs = (newTime - lastTime).count();
    const auto deltaTicks = static_cast<float>(newTicks - lastTicks);
    double ret = durToSecs * deltaTicks / durSecs;
    lastTime = newTime;
    lastTicks = newTicks;
    return ret;
}
