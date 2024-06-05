#pragma once

#include <iostream>

template <typename T> class bpointer;

template <typename T> class shared_region {
  friend class bpointer<T>;
  T *ref;

public:
  size_t refcount;

  shared_region(T *t) : ref(t), refcount{1} {};

  ~shared_region() {
    std::cout << "~shared region" << std::endl;
    delete (ref);
  }
};

template <typename T> class bpointer {
  shared_region<T> *ss;

public:
  bpointer() : ss(nullptr){};

  bpointer(T *t) { ss = new shared_region<T>(t); }

  T *operator->() {
    if (ss != nullptr) {
      return ss->ref;
    } else {
      return nullptr;
    };
  }

  void operator=(const bpointer<T> &rhs) {
    std::cout << "Assigment" << std::endl;
    ss = rhs.ss;
    if (ss != nullptr) {
      ++ss->refcount;
    }
  }

  bpointer(const bpointer<T> &rhs) {
    std::cout << "copy ctor" << std::endl;
    ss = rhs.ss;
    ++ss->refcount;
  }

  ~bpointer() {
    if (ss != nullptr) {
      std::cout << "~bpointer dtor refcount " << ss->refcount << std::endl;
      if (--ss->refcount == 0) {
        delete (ss);
      }
    } else {
      std::cout << "Destroying ptr with no share!" << std::endl;
    }
  }
};
