#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

struct Doit {
  atomic<int> counter;
  mutex m;

  Doit() : counter{0}, m{} {};

  void doit() {
    lock_guard<mutex>{m};
    counter++;
  }
};

int main(int argc, char *argv[]) {
  Doit doit;
  vector<thread> threads;
  threads.push_back(thread([&doit]() {
    for (int i = 0; i < 11; ++i) {
      doit.doit();
    };
  }));
  threads.push_back(thread([&doit]() {
    for (int i = 0; i < 11; ++i) {
      doit.doit();
    };
  }));
  threads.push_back(thread([&doit]() {
    for (int i = 0; i < 11; ++i) {
      doit.doit();
    };
  }));
  for (auto &x : threads) {
    cout << "Joining " << endl;
    x.join();
  }
  cout << "We have count of " << doit.counter << endl;
}
