#pragma once

#include <cstdint>
#include <ostream>

struct Trade {
  uint64_t time;
  uint32_t type;
  uint32_t inst;
  float bid;
  float ask;
};

std::ostream &operator<<(std::ostream &os, const Trade &t);
