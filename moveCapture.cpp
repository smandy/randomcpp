#include <future>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

class Foo {
  const std::string s;

public:
  Foo(const std::string &_s) : s(_s) {
    std::cout << "Foo(" << s << ")"
              << "\n";
  }

  std::string use(int n) {
    std::cout << "Foo " << s << " has been used"
              << "\n";
    std::ostringstream ret;
    ret << s << n;
    return ret.str();
  }

  ~Foo() {
    std::cout << "~foo"
              << "\n";
  }
};

template <typename T> class TR;

int main(int argc, char *argv[]) {
  auto foo = std::make_shared<Foo>("Woot");

  auto handle = std::async(std::launch::async,
                           [foo = std::move(foo)]() { return foo->use(42); });
  // TR<decltype(handle)> handleType;
  std::cout << handle.get() << "\n";
}
