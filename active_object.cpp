#include "tbb/concurrent_queue.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

template <typename T> struct TD;

using VoidFunc = void();
using VoidIntFunc = void(int, int);

using Message = std::function<VoidFunc>;

// TD<VoidIntFunc> Message2;
// TD<std::function<void(int,int)>::first_argument_type> ign2;

struct ActiveObject {
  bool done;
  tbb::concurrent_bounded_queue<Message> message_queue;
  std::thread t;

  ActiveObject()
      : done{false}, message_queue{}, t{[this]() {
          // std::cout << "Thread start" << std::endl;
          Message msg{};
          while (!done) {
            // std::cout << "Size is " << message_queue.size() << std::endl;
            message_queue.pop(msg);
            msg();
          }
        }} {}

  ~ActiveObject() {
    send([this]() {
      // std::cout << "Setting done" << std::endl;
      done = true;
    });
    t.join();
  }
  void send(Message msg) { message_queue.push(msg); }
  void join() { t.join(); }
};

struct Foo {
  int n;

  Foo() : n{} {};

  void inc() {
    n++;
    std::cout << "Inc!" << n << std::endl;
  }
};

struct Goo {
  int n;
  Goo() : n{} {}

  void operator()() {
    n++;
    std::cout << "Goo Inc " << n << "!" << std::endl;
  }
};

struct Doo : public std::enable_shared_from_this<Doo> {
  int n;

  Doo() : n{} {}
  void inc() {
    n++;
    std::cout << "Doo Inc " << n << "!" << std::endl;
  }
};

void wibble() { std::cout << "Wibble!!" << std::endl; };

int main() {
  Foo f;
  Goo g;
  int x{};

  auto d2 = std::make_shared<Doo>();
  auto d3 = std::bind(&Doo::inc, d2);
  auto b = std::bind(&Foo::inc, &f);
  auto call_g = [&]() {
    std::cout << "Lambda tastic" << std::endl;
    g();
  };

  Message my_msg{[&]() { ++x; }};
  {
    ActiveObject obj;
    ActiveObject obj2;

    std::thread t{[&]() {
      obj.send([]() { std::cout << "tWoot" << std::endl; });
      obj.send([]() { std::cout << "tPoot" << std::endl; });
      obj.send([]() { std::cout << "tBloot" << std::endl; });
    }};

    std::thread t2{[&]() {
      obj.send([]() { std::cout << "t2Woot" << std::endl; });
      obj.send([]() { std::cout << "t2Poot" << std::endl; });
      obj.send([]() { std::cout << "t2Bloot" << std::endl; });
    }};

    obj.send([]() { std::cout << "Woot" << std::endl; });
    obj.send([]() { std::cout << "Poot" << std::endl; });
    obj.send([]() { std::cout << "Bloot" << std::endl; });
    obj.send([]() { std::cout << "Soot" << std::endl; });
    obj.send([]() { std::cout << "Goot" << std::endl; });
    obj.send([&]() { std::cout << x++ << std::endl; });
    obj.send([&]() { std::cout << x++ << std::endl; });
    obj.send([&]() { std::cout << x++ << std::endl; });

    obj.send(my_msg);
    obj.send(my_msg);
    obj.send(my_msg);

    obj.send(wibble);

    obj.send(b);
    obj.send(b);
    obj.send(b);

    obj.send(g);
    obj.send(call_g);

    obj.send(d3);
    obj.send(d3);
    obj.send(d3);
    obj.send(d3);
    obj.send(d3);

    t.join();
    t2.join();
    obj2.send([]() { std::cout << "Hello from obj2" << std::endl; });
    obj2.send([]() { std::cout << "Hello again from obj2" << std::endl; });
    obj2.send([]() { std::cout << "Last message from obj2" << std::endl; });
    std::thread t3{[&]() {
      for (int i = 0; i < 4; ++i) {
        obj2.send([=]() { std::cout << "I all is now  " << i << std::endl; });
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      };
    }};
    t3.join();
  }

  std::cout << "All done x is " << x << std::endl;
  std::cout << "Foo n is " << f.n << std::endl;
  std::cout << "Goon is " << g.n << std::endl;
  std::cout << "Doon " << d2->n << std::endl;
}
