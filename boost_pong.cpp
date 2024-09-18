#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <chrono>

int main() {
    using namespace boost::interprocess;
    using Clock = std::chrono::high_resolution_clock;

    const std::size_t MEM_SIZE = sizeof(uint32_t);
    const uint64_t TOTAL_EVENTS = 500'000'000;
    const uint64_t REPORT_INTERVAL = (1 << 24); //10'000'000; // Report every 10 million events

    // Open the shared memory object.
    shared_memory_object shm(open_only, "PingPongMemory", read_write);

    // Map the shared memory.
    mapped_region region(shm, read_write);
    uint32_t* data = static_cast<uint32_t*>(region.get_address());

    std::cout << "Pong process started.\n";

    uint64_t events_processed = 0;
    Clock::time_point last_report_time = Clock::now();

    for (uint64_t i = 0; i < TOTAL_EVENTS; ++i) {
        // Wait for ping (data becomes non-zero).
        while (*data == 0);

        // Respond to ping by resetting data to zero.
        *data = 0;

        events_processed++;

        // Report progress every REPORT_INTERVAL events
        if (events_processed % REPORT_INTERVAL == 0) {
            auto current_time = Clock::now();
            auto time_diff = std::chrono::duration<double>(current_time - last_report_time).count();

            std::cout << "Pong processed " << events_processed << " events. "
                      << "Time since last report: " << time_diff << " seconds.\n";

            last_report_time = current_time;
        }
    }

    std::cout << "Pong process finished after processing " << TOTAL_EVENTS << " events.\n";
    return 0;
}
