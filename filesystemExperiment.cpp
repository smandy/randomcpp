#include <algorithm>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>

using namespace boost::filesystem;

int main(int argc, char *argv[]) {
  path p("/tmp");
  std::for_each(directory_iterator(p), directory_iterator(),
                [](auto &t) { std::cout << t << std::endl; });
}
