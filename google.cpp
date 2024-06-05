#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>

struct Point {
  int x;
  int y;
};

using pint = std::tuple<int, int>;

int solve(std::vector<Point> &&points) {
  int answer{};
  //    std::unordered_map<Point> count;
  std::map<pint, int> count;
  for (auto &p1 : points) {
    for (auto &p2 : points) {
      pint ps = {p1.y, p2.y};
      if (p1.x == p2.x && p1.y < p2.y) {
        answer += count[ps];
        count[ps]++;
      }
    }
  }
  return answer;
}

int main(int argc, char *argv[]) {
  auto x = solve({{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1}});
  std::cout << x << std::endl;
  return 0;
}
