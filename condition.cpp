#include <condition_variable>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

int _fib(int n) {
  if (n < 3) {
    return 1;
  } else {
    return _fib(n - 1) + _fib(n - 2);
  }
}

auto fib(int n) {
  // cout << "Starting " << n << endl;
  auto ret = _fib(n);
  // cout << "Ending   " << n << " -> " << ret << endl;
  return make_tuple(n, ret);
}

using FT = decltype(fib(0));
using LockType = unique_lock<mutex>;
// using LockGuard = lock_guard<mutex>;

template <typename T> class TD;

template <int N, int M, typename... TS> struct TuplePrinter {
  static inline void printElement(tuple<TS...> &t) {
    cout << get<N>(t);
    cout << ",";
    TuplePrinter<N + 1, M - 1, TS...>::printElement(t);
  }
};

template <int N, typename... TS> struct TuplePrinter<N, 0, TS...> {
  static inline void printElement(tuple<TS...> &t) { cout << get<N>(t); }
};

template <typename... TS> void printOne(tuple<TS...> &t) {
  cout << "(";
  TuplePrinter<0, sizeof...(TS) - 1, TS...>::printElement(t);
  cout << ")";
};

template <typename T> void printOne(T &t) { cout << t; }

template <typename T, typename Alloc,
          template <class, class> class ContainerType>
void print(ContainerType<T, Alloc> &t) {
  string sep("");
  cout << "[";
  for (auto &s : t) {
    cout << sep;
    printOne(s);
    sep = ", ";
  };
  cout << "]";
}

int main(int argc, char *argv[]) {
  mutex m;
  condition_variable cv;
  cout << "Acquire" << endl;
  vector<int> fibs{10, 20, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42};
  vector<FT> results;
  vector<thread> threads;

  for (const auto x : fibs) {
    cout << "Schedule " << x << endl;
    auto y = 2;
    threads.push_back(thread([&, x, y]() {
      // cout << "Running" << endl;_yft
      auto x2 = fib(x);
      {
        LockType lt(m);
        results.push_back(x2);
      }
      cv.notify_all();
    }));
  }

  auto running = true;
  vector<FT> myResults, tmp;
  while (running) {
    // NB unique lock unlocks on destruction if owned - '}' operator takes care
    // of it
    {
      LockType lk(m);
      cv.wait(lk, [&]() { return !results.empty(); });
      // Drain results into tmp buffer. This will be a move.
      swap(tmp, results);
    }
    myResults.insert(end(myResults), begin(tmp), end(tmp));
    tmp.clear();
    print(myResults);
    if (myResults.size() >= fibs.size()) {
      running = false;
    };
    cout << endl;
  }
  for (auto &t : threads) {
    t.join();
  }
}
