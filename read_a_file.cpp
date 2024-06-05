#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream ss("/home/andy/temp.csv");
  for (std::string line; getline(ss, line);) {
    std::cout << "Woot got a line " << line << std::endl;
  }
}
