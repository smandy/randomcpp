#include <functional>
#include <iostream>
#include <map>
#include <memory>

class DynClass;
using DynClassRP = std::shared_ptr<DynClass>;

class Factory {
public:
  static std::map<std::string, std::function<DynClassRP(void)>> registry;

public:
  static void registerClass(const std::string name,
                            std::function<DynClassRP(void)> fun) {
    registry[name] = fun;
  }

  static Factory &get() {
    static Factory instance;
    return instance;
  }

  template <typename T> T create(const std::string &name) {
    return std::static_pointer_cast<typename T::element_type, DynClass>(
        registry[name]());
    // return static_cast<T>(registry[name]());
  }
};

std::map<std::string, std::function<DynClassRP(void)>> Factory::registry{};

class DynClass {
  static DynClassRP create();
};

class FooClass;
using FooClassRP = std::shared_ptr<FooClass>;

class FooClass : public DynClass {
public:
  static bool registerClass() {
    Factory::get().registerClass("foo", FooClass::create);
    return true;
  }

  static FooClassRP create() { return std::make_shared<FooClass>(); }

  void call() { std::cout << "Woot" << std::endl; }
};

static bool register_foo = FooClass::registerClass();

int main(int argv, char *argc[]) {
  auto foo = Factory::get().create<FooClassRP>("foo");
  foo->call();
}
