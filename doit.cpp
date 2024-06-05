
#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>

using namespace std;

struct dumper {
  template <typename T> static void dump(T &xs) {
    string spacer("");
    cout << "{{";
    for_each(
        begin(xs), end(xs), [&](auto &p) {
          cout << spacer;
          cout << "{";
          cout << p.first << ", " << p.second;
          cout << "}";
          spacer = ",";
        }
             );
    cout << "}}";
  }

  template <typename T> static void dump(vector<T> &xs) {
    string spacer("");
    cout << "[";
    for_each(begin(xs), end(xs), [=, &spacer](auto &p) {
      cout << spacer;
      cout << p;
      spacer = ",";
    });
    cout << "]";
  }
};

int main(int argc, char *argv[]) {
  vector<int> myvec{1, 2, 3};

  dumper::dump(myvec);
  cout << endl;

  unordered_map<int, int> myMap = {{1, 2}, {3, 4}};

  dumper::dump(myMap);

  cout << "\nWoohoo\n";

  map<int, int> myMap2 = {{1, 2}, {3, 4}};

  dumper::dump(myMap2);
  cout << endl;
};
