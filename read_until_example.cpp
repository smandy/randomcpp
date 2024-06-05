#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <cstdlib>
#include <iostream>

using boost::asio::ip::tcp;

class session {
public:
  session(boost::asio::io_service &io_service) : socket_(io_service) {}

  tcp::socket &socket() { return socket_; }

  void start() {
    std::cout << "starting" << std::endl;
    boost::asio::async_read_until(
        socket_, buffer, ' ',
        boost::bind(&session::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void handle_read(const boost::system::error_code &error,
                   size_t bytes_transferred) {

    std::ostringstream ss;
    ss << &buffer;
    std::string s = ss.str();
    std::cout << s << std::endl;

    if (!error) {
      boost::asio::async_write(socket_, boost::asio::buffer(s),
                               boost::bind(&session::handle_write, this,
                                           boost::asio::placeholders::error));
    } else {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code &error) {
    std::cout << "handling write" << std::endl;
    if (!error) {
    } else {
      delete this;
    }
  }

private:
  tcp::socket socket_;
  boost::asio::streambuf buffer;
};

class server {
public:
  server(boost::asio::io_service &io_service, short port)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    session *new_session = new session(io_service_);
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&server::handle_accept, this,
                                       new_session,
                                       boost::asio::placeholders::error));
  }

  void handle_accept(session *new_session,
                     const boost::system::error_code &error) {
    if (!error) {
      new_session->start();
      new_session = new session(io_service_);
      acceptor_.async_accept(new_session->socket(),
                             boost::bind(&server::handle_accept, this,
                                         new_session,
                                         boost::asio::placeholders::error));
    } else {
      delete new_session;
    }
  }

private:
  boost::asio::io_service &io_service_;
  tcp::acceptor acceptor_;
};

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    using namespace std; // For atoi.
    server s(io_service, atoi(argv[1]));

    io_service.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
