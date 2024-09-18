#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <chrono>
#include <iostream>

int main()
{
    using namespace boost::interprocess;
    using Clock = std::chrono::high_resolution_clock;

    const std::size_t MEM_SIZE = sizeof(uint32_t);
    const uint64_t TOTAL_EVENTS = 500'000'000;
    const uint64_t REPORT_INTERVAL = (1 << 24); // 10'000'000; // Report every 10 million events

    // Open the shared memory object.
    shared_memory_object shm(open_or_create, "PingPongMemory", read_write);
    shm.truncate(MEM_SIZE);

    // Map the shared memory.
    mapped_region region(shm, read_write);
    uint32_t* data = static_cast<uint32_t*>(region.get_address());

    // Initialize shared memory
    *data = 0;

    std::cout << "Ping process started.\n";

    uint64_t events_processed = 0;
    Clock::time_point start_time = Clock::now();
    Clock::time_point last_report_time = start_time;

    // Start ping-pong loop
    for (uint64_t i = 0; i < TOTAL_EVENTS; ++i) {
        // Ping sends a signal (incrementing the value)
        *data = i + 1;

        // Wait for pong response (data becomes zero again)
        while (*data != 0)
            ;

        events_processed++;

        // Report progress every REPORT_INTERVAL events
        if (events_processed % REPORT_INTERVAL == 0) {
            auto current_time = Clock::now();
            auto time_diff = std::chrono::duration<double>(current_time - last_report_time).count();
            double latency_per_event = (time_diff / REPORT_INTERVAL) * 1e6; // Convert to microseconds

            std::cout << "Processed " << events_processed << " events. "
                      << "Latency per event: " << latency_per_event << " µs.\n";

            last_report_time = current_time;
        }
    }

    // Final report
    auto total_time = std::chrono::duration<double>(Clock::now() - start_time).count();
    std::cout << "Processed " << TOTAL_EVENTS << " events in " << total_time << " seconds.\n";
    std::cout << "Average latency per event: " << (total_time / TOTAL_EVENTS) * 1e6 << " us.\n";

    // Clean up
    shared_memory_object::remove("PingPongMemory");
    std::cout << "Ping process finished.\n";
    return 0;
}
