#include <iostream>

using namespace std;

class NullLogging {

public:
  void initLogging() { cout << "NullLogging:: init " << endl; }

  void doLog(const std::string &s) { cout << "log " << s << endl; }

  std::string getType() { return "NullLogging "; }
};

class AggressiveLogging {
public:
  void initLogging() { cout << "AggressiveLogging:: init " << endl; }

  void doLog(const std::string &s) { cout << "arse! " << s << endl; }

  std::string getType() { return "AggressiveLogging "; }
};

template <typename LogTraits = NullLogging>
class PolyLogger : public LogTraits {
public:
  int x;

  // See here
  // http://stackoverflow.com/questions/9941987/there-are-no-arguments-that-depend-on-a-template-parameter
  using LogTraits::doLog;
  using LogTraits::getType;
  using LogTraits::initLogging;

  PolyLogger() { initLogging(); };

  void mainLoop() {
    doLog("Foo");
    doLog("Bar");
  };
};

template <typename LoggerType> void greet(LoggerType &f) {
  f.doLog("Hello " + f.getType());
}

int main(int argc, char *argv[]) {
  using MyLogger = PolyLogger<>;
  using MuthaLogger = PolyLogger<AggressiveLogging>;

  MyLogger x;
  x.doLog("woot");
  greet(x);

  MuthaLogger mf;
  mf.doLog("Wayhey");
  greet(mf);
}
