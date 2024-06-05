#include "vwap.h"

#include "trade.h"

vwap::vwap() : qty{}, volume{} {};

float vwap::call(Trade &trade) {
  qty += 1;
  volume += (trade.bid + trade.ask) / 2.0;
  return get();
};

float vwap::call(Trade &&trade) {
  qty += 1;
  volume += (trade.bid + trade.ask) / 2.0;
  return get();
};

float vwap::get() { return qty == 0 ? 0.0 : volume / qty; };
