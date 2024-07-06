#include "tradeServer.h"

int main()
{
    trade_server cs{9876};
    cs.run();
}
