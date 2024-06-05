#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {

  auto sz = fs::file_size("tradedata");
  std::cout << "Size is " << sz << std::endl;

  auto fs = fs::temp_directory_path();
  std::cout << "Temp directory is " << fs << std::endl;
  return 0;
}
