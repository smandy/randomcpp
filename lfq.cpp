#include <atomic>
#include <boost/lockfree/queue.hpp>
#include <chrono>
#include <iostream>
#include <thread>

namespace blf = boost::lockfree;

template <typename T> class ReadWrite {
  blf::queue<T> &myQueue;
  T t;
  T tread;

  long readPad1, readPad2, readPad3, readPad4u;
  std::atomic<long> numReads;
  long readPad6, readPad7, readPad8;

  long writePad1, writePad2, writePad3, writePad4;
  std::atomic<long> numWrites;
  long writePad6, writePad7, writePad8;

public:
  ReadWrite(blf::queue<T> &_myQueue)
      : myQueue(_myQueue), t(), tread(), numReads(0), numWrites(0) {
    std::cout << "Mask is " << MASK << std::endl;
  }

  static constexpr auto MASK = (1 << 22) - 1;

  void doWrites() {
    while (true) {
      myQueue.push(t++);
      numWrites++;
      if ((numWrites & MASK) == 0) {
        std::cout << "Writer Reads : " << numReads << " Writes : " << numWrites
                  << std::endl;
      }
    }
  }

  void doReads() {
    while (true) {
      myQueue.pop(tread);
      numReads++;
      if ((numReads & MASK) == 0) {
        std::cout << "Reader Reads : " << numReads << " Writes : " << numWrites
                  << " read : " << tread << std::endl;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  blf::queue<int> myQueue(2048); // ( * 10 2 )

  ReadWrite<int> readWrite(myQueue);

  std::thread writer(&ReadWrite<int>::doWrites, &readWrite);
  std::thread reader(&ReadWrite<int>::doReads, &readWrite);

  writer.join();
  reader.join();
}
