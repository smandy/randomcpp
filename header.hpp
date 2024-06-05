#pragma once

#include <atomic>

using namespace std;

#pragma pack(push, 1)
struct PaddedLong {
private:
  uint64_t preamble[8];

public:
  atomic<uint64_t> value;

private:
  uint64_t postAmble[7];
};
#pragma pack(pop)

template <int Consumers> struct Header {
  PaddedLong reserveTail;
  PaddedLong commitTail;
  PaddedLong heads[Consumers];
};
