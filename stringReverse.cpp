#include <cstring>
#include <iostream>

void reverse(char s[]) {
  size_t len = strlen(s);
  char *end = s + len - 1;
  while (end > s) {
    char tmp = *s;
    *s++ = *end;
    *end-- = tmp;
  }
}

int main(int argc, char *argv[]) {
  std::string s{"wanker"};
  reverse(const_cast<char *>(s.c_str()));
  std::cout << s << std::endl;
}
