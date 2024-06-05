#include <algorithm>
#include <complex>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

#include "pretty_printer.hpp"

int moves[][2] = {{1, 2},   {2, 1},   {2, -1}, {1, -2},
                  {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

template <typename type1, typename type2> struct PairSorter {
  bool operator()(std::pair<type1, type2> p1, std::pair<type1, type2> p2) {
    return p2.second < p1.second;
  }
};

static const int BOARDSIZE = 8;
using Coord = std::complex<int>;

struct complexEqual {
  inline bool operator()(const Coord &c1, const Coord &c2) const {
    bool ret = (c1.real() * BOARDSIZE + c1.imag()) <
               (c2.real() * BOARDSIZE + c2.imag());
    return ret;
  }
};

typedef std::map<Coord, int, complexEqual> BoardType;

class Strategy {
public:
  int moves;
  Coord currentPosition;
  std::vector<std::vector<Coord>> possibleMoves;
};

class Board {
public:
  Board();
  BoardType board;
  Coord theMoves[BOARDSIZE];
  Coord currentPosition;
  int currentMove;
  int maxMoves;
  int movesMade;
  int solutionsFound;
  std::vector<Coord> validMoves();
  std::vector<Coord> sortedValidMoves();
  std::vector<Coord> moveHistory;
  bool emptySquare(const Coord &z);
  bool isOnBoard(const Coord &z);
  void makeMove(const Coord &z);
  std::vector<std::vector<Coord>> strategy;
  void dumpBoard();
  void rollback();

  PairSorter<Coord, int> mySorter;
};

void Board::dumpBoard() {
  std::cout << " Current : " << currentMove << " Max : " << maxMoves
            << std::endl;
  std::cout << "===================" << std::endl;
  for (int i = 0; i < BOARDSIZE; i++) {
    for (int j = 0; j < BOARDSIZE; j++) {

      Coord c(i, j);
      std::cout.width(3);
      std::cout.fill(' ');
      if (emptySquare(c)) {
        std::cout << " ";
      } else {
        std::cout << board[c];
      }
    }
    std::cout << std::endl;
  }
}

Board::Board() : currentMove(), maxMoves(), movesMade() {
  for (int i = 0; i < BOARDSIZE; i++) {
    theMoves[i] = Coord(moves[i][0], moves[i][1]);
    std::cout << " Move " << i << " is " << theMoves[i] << std::endl;
  }
  makeMove(Coord(0, 0));
}

void Board::makeMove(const Coord &z) {
  Coord dest = z + currentPosition;
  board[dest] = ++currentMove;
  moveHistory.push_back(z);
  currentPosition = dest;
  ++movesMade;

  if ((movesMade % 100000) == 0) {
    std::cout << movesMade << " moves ..." << std::endl;
  }

  if (currentMove > maxMoves || currentMove == 64) {
    maxMoves = currentMove;
    solutionsFound++;
    if (solutionsFound % 1000 == 0) {
      std::cout << solutionsFound << " solutions found" << std::endl;
      dumpBoard();
    }
  }
}

void Board::rollback() {
  Coord lastMove = moveHistory.back();
  moveHistory.pop_back();
  board.erase(currentPosition);
  currentPosition -= lastMove;
  --currentMove;
}

bool Board::emptySquare(const Coord &z) { return board.find(z) == board.end(); }

inline bool Board::isOnBoard(const Coord &z) {
  return (z.real() >= 0 && z.real() < BOARDSIZE && z.imag() >= 0 &&
          z.imag() < BOARDSIZE);
}

std::vector<Coord> Board::validMoves() {
  std::vector<Coord> ret;
  for (int i = 0; i < BOARDSIZE; i++) {
    Coord candidate = currentPosition + theMoves[i];
    if (isOnBoard(candidate) && emptySquare(candidate)) {
      ret.push_back(theMoves[i]);
    }
  }
  return ret;
}

std::vector<Coord> Board::sortedValidMoves() {
  std::vector<Coord> orig = validMoves();
  std::vector<std::pair<Coord, int>> ratedMoves;

  for (size_t i = 0; i < orig.size(); i++) {
    Coord c = orig[i];
    makeMove(c);
    ratedMoves.push_back(std::pair<Coord, int>(c, validMoves().size()));
    rollback();
  }

  sort(ratedMoves.begin(), ratedMoves.end(), mySorter);

  std::vector<Coord> ret;
  for (size_t i = 0; i < ratedMoves.size(); i++) {
    ret.push_back(ratedMoves[i].first);
  }
  return ret;
}

class BoardTest {
public:
  Board b;
  BoardTest(Board theBoard) : b(theBoard) {
    // Bootstrap the algorithm
    b.strategy.push_back(b.sortedValidMoves());
    while (1) {
      if (b.strategy.back().size() == 0) {
        b.rollback();
        b.strategy.pop_back();
        continue;
      } else {
        Coord moveToMake = b.strategy.back().back();
        b.strategy.back().pop_back();
        b.makeMove(moveToMake);
        b.strategy.push_back(b.sortedValidMoves());
      }
    }
  }
};

int main(int, char *[]) {
  Board theBoard;
  BoardTest bt(theBoard);
  return 0;
}
