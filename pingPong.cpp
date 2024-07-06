#include "pingPong.h"
#include "fcntl.h"

namespace argoko
{

PingPong::PingPong()
    : pingMap("/tmp/ping.dat", 8, O_RDWR | O_CREAT, true),
      pongMap("/tmp/pong.dat", 8, O_RDWR | O_CREAT, true){};

const int PingPong::REPORT_EVERY = 10000000;

}; // namespace argoko
