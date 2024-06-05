#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <cstdint>

namespace argoko {
class MMapper {
public:
  MMapper(const std::string &fn, const uint32_t size, const int mode,
          const bool expand);

  virtual ~MMapper();

  void close();

  const std::string fn;
  const uint32_t size;
  const int mode;
  bool closed;
  int fd;
  void *map;

  inline void *get() { return map; };
};
}; // namespace argoko
