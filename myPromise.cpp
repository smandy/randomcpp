#include <functional>
#include <future>
#include <iostream>
#include <thread>

void waitForInt(std::future<int> &fut) {
  auto x = fut.get();
  std::cout << "Woot got " << x << std::endl;
}

int main(int argc, char *argv[]) {
  std::promise<int> myPromise;

  std::future<int> fut = myPromise.get_future();
  std::thread t2{waitForInt, std::ref(fut)};

  std::cout << "Sending " << std::endl;
  myPromise.set_value(42);
  std::cout << "sent " << std::endl;

  std::cout << "Joining" << std::endl;
  t2.join();

  std::cout << "All done" << std::endl;
}
