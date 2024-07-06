#include <atomic>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <thread>
#include <time.h>

constexpr uint64_t REPETITIONS = 500 * 1000 * 1000;

void pongThread(std::atomic<uint64_t>& pingCounter,
                std::atomic<uint64_t>& pongCounter)
{
    std::cout << "Pongthread start" << std::endl;
    for (uint64_t i = 0; i < REPETITIONS; ++i) {
        while (pingCounter.load() != i) {
        }
        pongCounter.store(i);
    }
}

void pingThread(std::atomic<uint64_t>& pingCounter,
                std::atomic<uint64_t>& pongCounter)
{
    std::cout << "Pingthread start" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (uint64_t i = 0; i < REPETITIONS; ++i) {
        pingCounter.store(i);
        while (pongCounter.load() != i) {
        };
    }
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::high_resolution_clock::now() - start)
                   .count();

    std::cout << "Nanos elapsed " << dur << std::endl;
    std::cout << "Nanos per op " << (static_cast<float>(dur) / (2 * REPETITIONS))
              << std::endl;
    std::cout << "Ops per second " << (1000000000 * 2 * REPETITIONS / dur)
              << std::endl;
}

uint64_t ClockGetTime()
{

    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
}

int main(int, char*[])
{
    std::cout << "Starting" << std::endl;
    std::atomic<uint64_t> pingCounter(0L);
    std::atomic<uint64_t> pongCounter(0L);

    std::cout << "Made counters*" << std::endl;
    std::thread t1(&pongThread, std::ref(pingCounter), std::ref(pongCounter));
    std::thread t2(&pingThread, std::ref(pingCounter), std::ref(pongCounter));

    std::cout << "t1 + t2 started" << std::endl;

    t1.join();
    t2.join();
    std::cout << "t1 + t2 joined" << std::endl;
}
