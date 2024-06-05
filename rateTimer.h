#pragma once 

#include <chrono>

class RateTimer {
  using hrc = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  using MyDuration = std::chrono::nanoseconds;

  TimePoint lastTime;
  uint64_t lastTicks;
  uint64_t resolution;
  double durToSecs;

public:
  RateTimer();
  double rateForTicks(uint64_t newTicks);
};
