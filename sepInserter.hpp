#pragma once

#include <algorithm>

template <typename T>
class SepInserter : public std::iterator<std::output_iterator_tag, T> {
  std::ostream &os;
  std::string sep;

public:
  SepInserter(std::ostream &_os) : os(_os), sep(""){};

  SepInserter &operator=(T const &s) {
    os << sep << s;
    sep = ",";
    return *this;
  };

  SepInserter &operator++() { return *this; };

  SepInserter &operator*() { return *this; };
};
