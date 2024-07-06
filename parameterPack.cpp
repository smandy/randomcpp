#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>
#include <utility>

struct Foo {
    Foo(int _x, int _y) : x(_x), y(_y){};
    int x;
    int y;
};

struct Goo {
    Goo(int _x, int _y, int _z) : x(_x), y(_y), z(_z){};
    int x;
    int y;
    int z;
};

template <size_t N>
struct Container {
    Container() : offset{}, buf{} {}

    size_t offset;
    // Array wont protect against overallocating at the end
    // but at least indexing should be protected
    std::array<uint8_t, N> buf;

    template <typename T, typename... Args>
    void emplace(Args&&... args)
    {
        std::cout << "Woot" << std::endl;
        std::cout << "Buf is  " << &buf << std::endl;
        std::cout << "THis is  " << this << std::endl;
        new (&buf[offset]) T(args...);
        offset += sizeof(T);
        std::cout << "Offset is now " << offset << std::endl;
    }
};

int main(int argc, char* argv[])
{
    Container<512> container;
    container.emplace<Foo>(10, 20);
    container.emplace<Foo>(30, 90);
    container.emplace<Goo>(101, 102, 103);
    container.emplace<Goo>(71, 72, 73);
    // new (&container.buf) Foo {2,3};
    int* x = reinterpret_cast<int*>(&container.buf[0]);
    for (int i = 0; i < 10; ++i) {
        std::cout << i << " : " << x[i] << std::endl;
    }
};
