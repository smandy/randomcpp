#pragma once

#include "trade.h"

struct vwap {
  int qty;
  float volume;

  vwap();

  float call(Trade &trade);

  float call(Trade &&trade);
  float get();
};
