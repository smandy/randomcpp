#include "mmapper.h"
#include <cstdint>
#include <fcntl.h>
#include <iostream>

#include "trade.h"
#include <iostream>

int main(int argc, char* argv[])
{
    argoko::MMapper mmap("tradedata", 20000 * 24, O_RDWR, false);

    Trade* trades = reinterpret_cast<Trade*>(mmap.get());

    for (int i = 0; i < 20000; ++i) {
        std::cout << trades[i] << std::endl;
    }
    // std::cout << trades[0] << std::endl;
}
