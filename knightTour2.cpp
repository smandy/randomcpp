#include "pretty_printer.hpp"
#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>
#include <cstdint>

#include <functional>

using Coord = std::complex<int16_t>;
using CoordVec = std::vector<Coord>;
using CoordVecVec = std::vector<CoordVec>;

static const std::uint16_t BOARDSIZE = 8;

// clang-format off
static const CoordVec knightMoves = {{ 1,  2},
                                     { 2,  1},
                                     { 2, -1},
                                     { 1, -2},
                                     {-1, -2},
                                     {-2, -1},
                                     {-2,  1},
                                     {-1,  2}};

// clang-format on
bool isOnBoard(const Coord &p) {
  return p.real() >= 0 && p.real() < BOARDSIZE && p.imag() >= 0 &&
         p.imag() < BOARDSIZE;
}

void calcPossibleMoves(const CoordVec &visited, CoordVec &dest) {
  dest.clear();
  for (auto &x : knightMoves) {
    auto candidate = visited.back() + x;
    if (isOnBoard(candidate) && std::find(visited.rbegin(), visited.rend(),
                                          candidate) == visited.rend()) {
      dest.push_back(candidate);
    }
  }
}

Coord bestMove(const CoordVec &moves, CoordVec &visited) {
  static thread_local CoordVec pm;
  auto it = std::begin(moves);
  Coord ret = *it;
  size_t bestLength = 9;
  std::for_each(std::begin(moves), std::end(moves), [&](auto &x) {
    visited.push_back(x);
    calcPossibleMoves(visited, pm);
    auto newLength = pm.size();
    visited.pop_back();
    if (newLength < bestLength) {
      bestLength = newLength;
      ret = x;
    }
  });
  return ret;
}

template <typename CbType>
void doTour(CbType &&cb, Coord startingPoint = {0, 0}) {
  static thread_local CoordVec pm;
  CoordVec visited = {startingPoint};
  calcPossibleMoves(visited, pm);
  CoordVecVec movesToMake = {pm}; // Copy
  bool running = true;
  while (running && !movesToMake.empty()) {
    auto &currentPossibleMoves = movesToMake.back();
    if (currentPossibleMoves.empty()) {
      movesToMake.pop_back();
      visited.pop_back();
    } else {
      auto moveToMake = bestMove(currentPossibleMoves, visited);
      currentPossibleMoves.erase(std::remove(begin(currentPossibleMoves),
                                             end(currentPossibleMoves),
                                             moveToMake),
                                 end(currentPossibleMoves));
      visited.push_back(moveToMake);
      if (visited.size() == (BOARDSIZE * BOARDSIZE)) {
        running = cb(CoordVec(begin(visited), end(visited)));
      }
      calcPossibleMoves(visited, pm);
      movesToMake.push_back(pm);
    }
  }
}

struct Foo {
    int count;
    
    bool cb( CoordVec &&vec) {
        std::cout << ++count << " :";
        print(std::cout, vec);
        std::cout << "\n";
        return true;
    };
};


int main(int, char *[]) {
  int x{};

  Foo foo;
  
  // doTour([&](auto vec) {
  //   std::cout << x << " : ";
  //   print(std::cout, vec);
  //   std::cout << std::endl;
  //   return ++x < 100;
  // });

  doTour( std::bind( &Foo::cb, &foo, std::placeholders::_1 ));
}
