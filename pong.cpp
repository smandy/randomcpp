#include "pingPong.h"
#include "rateTimer.h"
#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
  argoko::PingPong pp;
  std::atomic<uint64_t> *ping = pp.ping();
  std::atomic<uint64_t> *pong = pp.pong();

  const uint64_t MASK = (2L << 22) - 1;
  uint64_t counter = 0;
  RateTimer rt;
  while (true) {
    counter += 1;
    while (ping[0].load(std::memory_order_acquire) != counter) {
    };
    pong[0].store(counter, std::memory_order_release);
    if ((counter & MASK) == 0) {
      std::cout << rt.rateForTicks(counter) << std::endl;
    }
  }
}
