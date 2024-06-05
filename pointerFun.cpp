#include <condition_variable>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace std;

using LockType = unique_lock<mutex>;
using LockGuard = lock_guard<mutex>;

mutex m;

struct Foo {
  Foo(int _x, int _y) : x(_x), y(_y) { cout << "Create foo" << endl; };

  ~Foo() { cout << "Im melting" << endl; };
  const int x;
  const int y;
};

using FooPtr = shared_ptr<const Foo>;

void dump(int ident, FooPtr f) {
  LockGuard lg(m);
  cout << "dump(" << ident << "," << f->x << "," << f->y << ")" << endl;
}

int main(int argc, char *argv[]) {
  vector<thread> mythreads;
  auto x2 = make_shared<const Foo>(10, 20);
  for (int x = 10; x > 0; --x) {
    mythreads.emplace_back(dump, x, x2);
  }

  for (auto &x : mythreads) {
    x.join();
  }

  cout << "clocking off " << endl;
}
