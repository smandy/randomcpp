#include <boost/algorithm/string.hpp>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <template <class> class f1, template <class> class f2>
struct or_combinator {
  template <class T> struct lambda {
    static const bool value = f1<T>::value || f2<T>::value;
  };
};

template <int N> struct is_one {
  enum { value = false };
};

template <> struct is_one<1> {
  enum { value = true };
};

template <int T, int U> struct IsEqual {
  enum { value = false };
};

template <int T> struct IsEqual<T, T> {
  enum { value = true };
};

template <int N> struct is_N {
  template <int M> struct functor {
    static const bool value = IsEqual<N, M>::value;
  };
};

template <bool Q, bool V> struct OR {
  enum { value = true };
};

template <> struct OR<false, false> {
  enum { value = false };
};

template <int X, int Y> struct IsEither {
  template <int Z> struct functor {
    enum {
      value = is_N<X>::template functor<Z>::value ||
              is_N<Y>::template functor<Z>::value
    };
  };
};

template <int... XS> struct IsAny;

template <> struct IsAny<> {
  template <int Z> struct functor {
    enum { value = false };
  };
};

template <int X, int... XS> struct IsAny<X, XS...> {
  template <int Z> struct functor {
    enum {
      value = is_N<X>::template functor<Z>::value ||
              IsAny<XS...>::template functor<Z>::value
    };
  };
};

template <typename T> void dump(const T &ts) {
  string sep("");
  cout << "[";
  for (const auto &t : ts) {
    cout << sep << t;
    sep = ",";
  };
  cout << "]" << endl;
}

template <template <class...> class Cont> class MyFunc {
  Cont<std::string> myCont;

public:
  MyFunc() : myCont() {
    myCont.push_back("Woohoo");
    dump(myCont);
  }
};

struct ScopeExit {
  typedef std::function<void()> VoidFunc;

  ~ScopeExit() { closure(); }

  ScopeExit(VoidFunc myFunc) : closure(myFunc) {}

private:
  VoidFunc closure;
};

int main(int argc, char *argv[]) {
  cout << "is_one<1> " << is_one<1>::value << endl;
  cout << "is_one<2> " << is_one<2>::value << endl;
  cout << "is_N<2>::functor<2>::value " << is_N<2>::functor<2>::value << endl;
  cout << "is_N<3>::functor<2>::value " << is_N<3>::functor<2>::value << endl;
  cout << "is_N<1>::functor<1>::value " << is_N<1>::functor<1>::value << endl;
  cout << "IsEither<1,2>::functor<1>::value "
       << IsEither<1, 2>::functor<1>::value << endl;
  cout << "IsEither<1,2>::functor<2>::value "
       << IsEither<1, 2>::functor<2>::value << endl;
  cout << "IsEither<1,2>::functor<3>::value "
       << IsEither<1, 2>::functor<3>::value << endl;

  cout << "IsAny<1,2,3>::functor<2>::value "
       << IsAny<1, 2, 3, 4, 5, 6, 7, 6, 9, 1, 2, 3, 4, 5, 6, 7, 6,
                9>::functor<2>::value
       << endl;
  cout << "IsAny<1,2,3>::functor<4>::value "
       << IsAny<1, 2, 3, 4, 5, 6, 7, 6, 9, 1, 2, 3, 4, 5, 6, 7, 6,
                9>::functor<20>::value
       << endl;

  string s1 = "Enclosing scope";

  ScopeExit([] { cout << "Im melting" << endl; });
  ScopeExit([] { cout << "Im melting2" << endl; });

  ScopeExit([&s1] { cout << "Im melting2" << s1 << endl; });

  auto c2 = [] { cout << "Woohoo I am a closure" << endl; };

  // auto f1 = [] (int x ) { return x * 2; };

  ScopeExit c3(c2);

  MyFunc<std::vector> myCont;
  MyFunc<std::deque> myCont2;
  MyFunc<std::list> myCont3;

  vector<string> myStrings{"foo", "bar", "baz", "goo", "noo"};
  dump(myStrings);

  std::ifstream ss;

  ss.open("/home/andy/andy.csv");
  for (string line; getline(ss, line);) {
    cout << "Woot got a line " << line << endl;
    vector<string> vec;
    boost::algorithm::split(vec, line, boost::is_any_of(","));
    dump(vec);
  }

  using IntFunc = std::pair<std::string, std::function<int(int, int)>>;

  vector<IntFunc> myFuncs{{"add", [](int x, int y) { return x + y; }},
                          {"mult", [](int x, int y) { return x * y; }},
                          {"sub", [](int x, int y) { return x - y; }}};

  for (auto &f : myFuncs) {
    auto ret = f.second(1, 2);
    cout << f.first << "(1,2) -> " << ret << endl;
  }
}
