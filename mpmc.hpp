#pragma once

#include "cassert"
#include "cstddef"
#include "header.hpp"
#include "limits"
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

template <typename T, int Consumers, int Capacity, int ConsumerId>
struct ManyToManyWriter {
  static constexpr auto MASK = Capacity - 1;
  static constexpr auto SIZE = sizeof(Header<Consumers>) + Capacity * sizeof(T);

  using HeaderType = Header<Consumers>;

  uint64_t cacheTail;
  uint64_t cacheHead;

  bool reserved;
  uint64_t reservedPos;
  uint64_t currentPos;

  HeaderType *header;
  T *data;
  void *ptr;

  ManyToManyWriter(const string &fn, const bool expand = true)
      : cacheTail(), cacheHead(), reserved(), reservedPos(), currentPos() {
    auto mode = O_RDWR | O_CREAT;
    auto fd = open(fn.c_str(), mode, (mode_t)0660);
    if (fd == -1) {
      perror("Error opening file for writing");
      exit(EXIT_FAILURE);
    }
    cout << "Opened file fd is " << fd << endl;
    if (expand) {
      int result = lseek(fd, SIZE - 1, SEEK_SET);
      if (result == -1) {
        ::close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
      }
      result = write(fd, "", 1);
      if (result != 1) {
        ::close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
      }
    }

    cout << "About to mmap" << endl;
    ptr = mmap(0, SIZE, mode, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
      ::close(fd);
      perror("Error mmapping the file");
      exit(EXIT_FAILURE);
    }
    cout << "Map is " << ptr << endl;

    header = static_cast<HeaderType *>(ptr);
    data = reinterpret_cast<T *>(reinterpret_cast<char *>(ptr) +
                                 sizeof(HeaderType));

    cout << "HEader is " << header << endl;
    cout << "Data   is " << data << endl;

    cacheTail = getTail();
    cout << "Tail is " << cacheTail << endl;
    cacheHead = getHead();
    cout << "Head is " << cacheHead << endl;
  }

  inline T &reserve() {
    assert(!reserved);
    // TODO - need postincrement!
    reservedPos = header->reserveTail.value.operator++(0);
    while (reservedPos - cacheHead >= Capacity) {
      cacheHead = getHead();
      // TODO - maybe yield here
    };
    reserved = true;
    return data[indexOf(reservedPos)];
  }

  inline void advance(int n) { currentPos += n; }

  inline void commitConsumed() {
    header->heads[ConsumerId - 1].value.store(currentPos);
    // cout << "committed " << header->heads[ConsumerId].value.load() << endl;
  }

  inline T &current() { return data[indexOf(currentPos)]; }

  inline uint32_t avail() {
    const auto firstStab = static_cast<int>(cacheTail - currentPos);
    if (firstStab > 0)
      return firstStab;
    cacheTail = getTail();
    auto ret = static_cast<int>(cacheTail - currentPos);
    // cout << "Avail is " << ret << cacheTail << " " << currentPos << endl;
    return ret;
  }

  inline void commit() {
    assert(reserved);
    while (!header->commitTail.value.compare_exchange_strong(reservedPos,
                                                             reservedPos + 1)) {
    };
    // cout << "Commit " << reservedPos << " -> " << reservedPos + 1 << " cf "
    // << header->commitTail.value.load() << endl;
    cacheTail = reservedPos + 1;
    reserved = false;
  }

  uint64_t getTail() {
    // cout << "GetTail" << endl;
    auto ret = header->commitTail.value.load();
    // cout << "Got " << ret << endl;
    return ret;
  }

  // TODO tmp
  inline auto getHead() {
    // cout << "getHead" << endl;
    //  auto ret = numeric_limits<uint64_t>::max();
    //  for ( int i = Consumers;i>0;--i) {
    //    //cout << "Loop " << i << endl;
    //    ret = min( ret, header->heads[i].value.load());
    //  };
    //  //cout << " Got " << ret << endl;
    // TODO fixup
    auto ret = header->heads[0].value.load();
    return ret;
  }

  static inline int indexOf(size_t n) { return static_cast<int>(n & MASK); }
};
