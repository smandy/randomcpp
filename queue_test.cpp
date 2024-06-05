#include "tbb/concurrent_queue.h"
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

using Message = std::function<void()>;

using Behaviour = std::function<void(Message &)>;

struct ActiveObject {
  std::string s_;
  bool done;
  tbb::concurrent_bounded_queue<Message> message_queue;
  std::thread t;

  ActiveObject(std::string s)
      : s_{s}, done{false}, message_queue{}, t{[=]() {
          Message msg{};
          // std::cout << s_ << " Thread start" << std::endl;
          while (!done) {
            // std::cout << s_ << " Size is " << message_queue.size() <<
            // std::endl;
            message_queue.pop(msg);
            // std::cout << s_ << "popped message" << std::endl;
            msg();
          };
        }} {
    std::cout << s_ << " Active object" << std::endl;
  }

  void join() { t.join(); }

  void send(Message msg) {
    // std::cout << s_ << " Sending .." << std::endl;
    message_queue.push(msg);
  }

  void die() {
    send([=]() { done = true; });
  }

  void ping(ActiveObject &target, size_t n) {
    // std::cout << s_ << " ping " << target.s_ << std::endl;
    if (n < 1000000) {
      if ((n & ((1 << 15) - 1)) == 0) {
        std::cout << s_ << "n is ..." << n << std::endl;
      };
      // std::cout << s_ << " About to send" << std::endl;
      send([=, &target]() {
        // std::cout << s_ << " Pinging the c*nt" << std::endl;
        // std::cout << s_ << " target is " << &target << " this is " << this <<
        // std::endl;
        target.ping(*this, n + 1);
      });
      // std::cout << s_ << " Ping done..." << std::endl;
    } else {
      std::cout << "Die" << std::endl;
      die();
      target.die();
    }
  }
};

int main() {
  ActiveObject a1{"a1"};
  ActiveObject a2{"a2"};

  a2.ping(a1, 0);

  a1.join();
  a2.join();
}
