#include <algorithm>
#include <boost/filesystem.hpp>
#include <iostream>
#include <iterator>
using namespace std;
using namespace boost::filesystem;

int main(int argc, char *argv[]) {
  path p{"/home/andy"};
  auto iter = directory_iterator(p);
  copy(directory_iterator(p),
       directory_iterator(), // directory_iterator::value_type
       ostream_iterator<directory_entry>(cout,
                                         "\n")); // is directory_entry, which is
  for_each(directory_iterator(p), directory_iterator(),
           [&](auto &de) { cout << "Wazoo " << de << endl; });

  // vector<std::string> strings { "foo", "bar", "baz"};
  // for( const string &s : strings) {
  //   cout << "Bazoo : " << s << endl;
  // };
}
