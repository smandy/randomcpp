#pragma once

#include "header.hpp"
#include "queueCommon.hpp"

#include "limits"

template <int T> struct TR;

using namespace std;

template <typename T, int Consumers, size_t Capacity>
struct ManyToManyCommon : public QueueCommon<T, Capacity> {
  using Base = QueueCommon<T, Capacity>;

public:
};
