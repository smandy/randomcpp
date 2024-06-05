#include "rateTimer.h"
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

static const auto MILLION = 1'000'000;

int main(int argc, char *argv[]) {
  RateTimer rt;
  auto ticks = 0;
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ticks += 2'000'000;
    cout << rt.rateForTicks(ticks) / MILLION << endl;
  }
}
