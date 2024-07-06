#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <typeinfo>

static inline int64_t tick()
{
    int64_t d;
    __asm__ __volatile__("rdtsc" : "=A"(d));
    return d;
}

int main()
{
    unsigned long long s1, dur;
    for (int i = 0; i < 5000; ++i) {
        s1 = tick();
        dur = tick() - s1;
        printf("tsc %lld\n", dur);
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;

    for (int i = 0; i < 5000; ++i) {
        start = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds =
            std::chrono::high_resolution_clock::now() - start;
        auto dur =
            std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds)
                .count();
        std::cout << "HRT Dur is nanos " << dur << std::endl;
    }

    for (int i = 0; i < 5000; ++i) {
        start = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds =
            std::chrono::system_clock::now() - start;
        auto dur =
            std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds)
                .count();
        std::cout << "System Clock Dur is nanos " << dur << std::endl;
    }
    return 0;
}
