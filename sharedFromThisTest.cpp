#include <iostream>
#include <memory>

class Foo : std::enable_shared_from_this<Foo> {
public:
  std::shared_ptr<Foo> clone() { return shared_from_this(); }
};

int main(int argc, char *argv[]) {
  std::cout << "Make foo" << std::endl;
  auto f = std::make_shared<Foo>();
  {
    std::cout << "Make g" << std::endl;
    auto g = f->clone();
    std::cout << "Kill g" << std::endl;
  }
  std::cout << "Kill f" << std::endl;
}
