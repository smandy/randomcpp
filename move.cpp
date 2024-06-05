#include <iostream>
#include <ostream>

struct Mover;

using namespace std;

ostream &operator<<(ostream &os, const Mover &mover);

struct Mover {
  Mover(const Mover &) = delete;
  Mover(string s_) : s(new string(s_)){};

  ~Mover() {
    cout << "Im melting " << *s << endl;
    delete (s);
  }

  void operator=(const Mover &) = delete;

  Mover(Mover &&rhs) {
    cout << "I like to move it move it " << rhs << endl;
    s = rhs.s;
    // delete rhs.s;
    rhs.s = NULL;
  }

  Mover &operator=(Mover &&rhs) {
    std::cout << "I like to assing it,  it assign it " << std::endl;
    s = rhs.s;
    rhs.s = NULL;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &, const Mover &);

private:
  string *s;
};

std::ostream &operator<<(ostream &os, const Mover &mover) {
  cout << "Mover(" << mover.s << "," << *mover.s << ")";
  return os;
}

// ostream &operator<<(  ostream &os, Mover &&mover) { cout << "Mover&&(" <<
// mover.s << "," << *mover.s << ")"; return os; };

void doit(Mover &&m) { cout << "Doit (" << m << ")" << endl; }

void doit2(const Mover &m) { cout << "Doit2 (" << m << ")" << endl; }

// ostream &operator<<( ostream &os, Mover &&mover) { cout << "Mover(" <<
// mover.s << "," << *mover.s << ")"; return os; };
int main(int argv, char *argc[]) {
  Mover m("foo");
  cout << m << endl;
  Mover m2 = std::move(m);

  cout << m2 << endl;
  doit(Mover("Wayhey"));

  Mover m4 = Mover("m4");
  cout << m4 << endl;

  Mover m5 = std::move(m4);

  cout << m5 << endl;
  doit2(Mover("Reference 2"));
};
