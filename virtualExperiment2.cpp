#include <iostream>

class IHead {
public:
  virtual void sharpen() = 0;
  virtual void clean() = 0;
};

class IHandle {
public:
  virtual void grab() = 0;
  virtual void swing() = 0;
};

class IHammer : public virtual IHead, public virtual IHandle {};

// Handles
class Elm : public virtual IHammer {
public:
  void swing() {
    std::cout << "Elm Swing" << std::endl;
    clean();
  }

  void grab() {
    std::cout << "Elm Grab" << std::endl;
    sharpen();
  }
};

class Oak : public virtual IHammer {
public:
  void swing() {
    std::cout << "Oak Swing" << std::endl;
    clean();
  }

  void grab() {
    std::cout << "Oak Grab" << std::endl;
    sharpen();
  }
};

// Heads
class Iron : public virtual IHammer {
public:
  void sharpen() {
    std::cout << "Iron Sharpen" << std::endl;
    swing();
  }
  void clean() { std::cout << "Iron clean" << std::endl; }
};

class Brass : public virtual IHammer {
public:
  void sharpen() {
    std::cout << "Brass Sharpen" << std::endl;
    swing();
  }
  void clean() { std::cout << "Brass clean" << std::endl; }
};

class BrassOak : public virtual Oak, public Brass {};

class IronElm : public virtual Iron, public Elm {};

class BrassElm : public virtual Elm, public Brass {};

int main(int argc, char *argv[]) {
  BrassOak hammer;
  hammer.grab();

  std::cout << std::endl;

  IronElm hammer2;
  hammer2.grab();

  std::cout << std::endl;

  BrassElm hammer3;
  hammer3.grab();
}
