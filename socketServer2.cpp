#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>

void error(const char *msg) {
  perror(msg);
  exit(1);
}

template <int BUFFERSIZE = 65536> class SocketServer {
  using ThisType = SocketServer<BUFFERSIZE>;

  using CallbackType = std::function<void(ThisType &, char *, int)>;
  int port;
  CallbackType listener;
  int sockfd, newsockfd;
  socklen_t clilen;
  char buffer[BUFFERSIZE];
  struct sockaddr_in serv_addr, cli_addr;

public:
  SocketServer(int _port, CallbackType _listener)
      : port(_port), listener(_listener) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
      error("ERROR opening socket");
    }

    bzero(reinterpret_cast<char *>(&serv_addr), sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    std::cout << "binding " << port << std::endl;
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      error("ERROR on binding");

    std::cout << "Listening " << sockfd << std::endl;
    listen(sockfd, 5);
    socklen_t clilen = sizeof(serv_addr);
    bzero(buffer, BUFFERSIZE);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    std::cout << "Accepted" << std::endl;
    if (newsockfd < 0)
      error("ERROR on accept");
    while (true) {
      auto n = read(newsockfd, buffer, BUFFERSIZE);
      if (n < 0)
        error("ERROR reading from socket");
      if (n > 0) {
        std::cout << "Got " << n << std::endl;
        listener(*this, buffer, n);
        bzero(buffer, n);
      };
    }
  }

  int write(char *buf, size_t n) { return ::write(newsockfd, buf, n); }

  int write(std::string &s) { return write(s.c_str(), s.size()); }

  ~SocketServer() {
    close(newsockfd);
    close(sockfd);
  }
};

int main(int argc, char *argv[]) {
  auto port = argc > 1 ? atoi(argv[1]) : 10666;
  std::cout << "port is " << port << std::endl;
  using MySock = SocketServer<>;
  MySock ss(port, [](MySock &s, char *buf, int sz) {
    std::cout << "Got " << sz << " bytes";
    s.write(buf, sz);
  });
}
