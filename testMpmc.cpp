#include "mpmc.hpp"
#include <thread>

using namespace std;

int main(int argc, char* argv[])
{
    constexpr auto MASK = (1 << 25) - 1;

    ManyToManyWriter<uint64_t, 1, 4096, 1> myWriter("/dev/shm/andy1.dat");
    ManyToManyWriter<uint64_t, 1, 4096, 1> myWriter2("/dev/shm/andy1.dat");

    auto looper = false;

    thread t2([&]() {
        uint64_t iters = (1 << 25) / 2;
        decltype(myWriter2.avail()) avail;
        while (iters < 256 || looper) {
            while ((avail = myWriter2.avail()) == 0) {
            };
            for (int i = avail; i > 0; --i) {
                if ((++iters & MASK) == 0) {
                    cout << "Receive " << myWriter2.current() << endl;
                };
                myWriter2.advance(1);
                myWriter2.commitConsumed();
            };
        };
    });

    thread t1([&]() {
        uint64_t iters = 0;
        while (iters < 256 || looper) {
            myWriter.reserve() = iters;
            myWriter.commit();
            // cout << "Commit " << iters << endl;
            if ((++iters & MASK) == 0) {
                cout << "Wrote " << myWriter.current() << endl;
            };
        };
    });

    t1.join();
    t2.join();
}
