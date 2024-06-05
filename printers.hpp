#include <ostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using namespace std;



template <typename A, typename B>
ostream &operator<<(ostream &os, const tuple<A, B> &t) {
  os << "(" << std::to_string(get<0>(t)) << "," << get<1>(t) << ")";
  return os;
};


template <typename A, typename B>
ostream &operator<<(ostream &os, map<A, B> &m) {
    std::string sep = "{";

    for_each( begin(m), end(m), [&](const auto &p) {
        os << sep;
        os << p.first << "=" << p.second;
    });
    os << "}";
  return os;
};



template <typename A, typename B, typename C>
ostream &operator<<(ostream &os, const tuple<A, B, C> &t) {
  os << "{" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << "}";
  return os;
};

template <typename A> ostream &operator<<(ostream &os, const vector<A> &v) {
  string sep = "[";
  for_each(begin(v), end(v), [&](auto &x) {
    os << sep;
    os << x;
    sep = ",";
  });

  os << "]";
  return os;
};

template <> ostream &operator<<(ostream &os, const vector<uint8_t> &v) {
  string sep = "[";
  for_each(begin(v), end(v), [&](auto &x) {
    os << sep;
    os << ( x == 1 ? "1" : "0");
    sep = ",";
  });

  os << "]";
  return os;
};

template <typename A, typename B>
ostream &operator<<(ostream &os, pair<A, B> t) {
  os << "(" << t.first << "," << t.second << ")";
  return os;
};
