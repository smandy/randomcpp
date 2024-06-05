#include "mmapper.h"
#include "tradeSource.hpp"

// template<typename T>
struct Listener {

  std::string s;

  Listener(std::string _s) : s(_s){};

  void onTrade(Trade &trade) { std::cout << s << " " << trade << std::endl; };
};

int main(int argc, char *argv[]) {
  Listener l1("network");
  Listener l2("file");

  network_trade_source<Listener> nts;
  nts.run(l1);

  file_trade_source<Listener> fts;
  fts.run(l2);

  return 0;
}
