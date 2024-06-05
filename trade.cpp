#include "trade.h"

std::ostream &operator<<(std::ostream &os, const Trade &t) {
  os << "Trade(";
  os << "time=" << t.time << " ";
  os << "type=" << t.type << " ";
  os << "inst=" << t.inst << " ";
  os << "bid=" << t.bid << " ";
  os << "ask=" << t.ask << " ";
  os << ")";
  return os;
};
