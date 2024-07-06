#include "mpmc.hpp"
#include <thread>

using namespace std;

int main(int argc, char* argv[])
{
    constexpr auto MASK = (1 << 25) - 1;

    ManyToManyWriter<uint64_t, 1, 4096, 1> myWriter("/dev/shm/andy4.dat");
    ManyToManyWriter<uint64_t, 1, 4096, 1> myWriter2("/dev/shm/andy4.dat");
    // Tmp
    // auto looper = true;

    constexpr auto MAX_ITER = 1000 * 1000 * 1000;

    thread t2([&]() {
        uint64_t iters = 0;
        decltype(myWriter2.avail()) avail;
        uint64_t count = 0;
        while (iters < MAX_ITER - 1) {
            while ((avail = myWriter2.avail()) == 0) {
            };
            for (int i = avail; i > 0; --i) {
                ++iters;
                count += myWriter2.current();
                if (((iters + 100000) & MASK) == 0) {
                    cout << "Receive " << myWriter2.current() << endl;
                };
                myWriter2.advance(1);
                myWriter2.commitConsumed();
            };
        };
        cout << "Woot " << count << endl;
    });

    thread t1([&]() {
        uint64_t count = 0;
        for (uint64_t iters = 0; iters < MAX_ITER; ++iters) {
            myWriter.reserve() = iters;
            count += iters;
            myWriter.commit();
            if ((iters & MASK) == 0) {
                cout << "Wrote " << myWriter.current() << endl;
            };
        };
        cout << " All don wrote " << count;
    });

    t1.join();
    t2.join();
}
