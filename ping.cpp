#include "pingPong.h"
#include "rateTimer.h"
#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
  argoko::PingPong pp;
  std::atomic<uint64_t> *ping = pp.ping();
  std::atomic<uint64_t> *pong = pp.pong();
  uint64_t counter = 0;
  const uint64_t MASK = (2L << 21) - 1;
  RateTimer rt;
  while (true) {
    ++counter;
    ping[0].store(counter, std::memory_order_release);
    while (pong[0].load(std::memory_order_acquire) != counter) {
    };
    if ((counter & MASK) == 0) {
      std::cout << "Rate is " << rt.rateForTicks(counter) << std::endl;
    }
  }
}
