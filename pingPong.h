#pragma once

#include "mmapper.h"
#include <atomic>

namespace argoko {
class PingPong {
public:
  PingPong();

  MMapper pingMap;
  MMapper pongMap;

  inline std::atomic<uint64_t> *ping() {
    return reinterpret_cast<std::atomic<uint64_t> *>(pingMap.get());
  };
  inline std::atomic<uint64_t> *pong() {
    return reinterpret_cast<std::atomic<uint64_t> *>(pongMap.get());
  };

  static const int REPORT_EVERY;
};
}; // namespace argoko
