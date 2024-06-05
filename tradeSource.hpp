#pragma once

#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

#include "mmapper.h"
#include "trade.h"

using boost::asio::ip::tcp;
using socket_type = boost::asio::ip::tcp::socket;
using errcode = boost::system::error_code;

using endpoints_type =
    boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>;

template <typename T> struct TD;

template <typename T, typename sink_type> struct trade_source {
  inline auto instance() { return *static_cast<T *>(this); }

  void run(sink_type &sink) { instance().run(sink); };
};

template <typename sink_type>
struct file_trade_source
    : public trade_source<file_trade_source<sink_type>, sink_type> {

  void run(sink_type &listener) {
    argoko::MMapper mmap("tradedata", static_cast<uint32_t>(20000 * 24), O_RDWR,
                         false);

    Trade *trades = reinterpret_cast<Trade *>(mmap.get());

    for (int i = 0; i < 20000; ++i) {
      listener.onTrade(trades[i]);
    }
  }
};

template <typename sink_type>
struct network_trade_source
    : public trade_source<network_trade_source<sink_type>, sink_type> {
  boost::asio::io_service ios;
  tcp::resolver resolver;
  endpoints_type endpoints;
  socket_type socket;

  char buffer[1000];

  network_trade_source()
      : ios{}, resolver{ios}, endpoints{resolver.resolve("localhost", "9876")},
        socket{ios}, buffer{} {};

  void do_read(sink_type &listener) {
    static Trade t;

    boost::asio::async_read(
        socket, boost::asio::buffer(&t, sizeof(Trade)),
        [this, &listener](const errcode &ec, std::size_t sz) {
          if (ec || sz != sizeof(Trade)) {
            std::cout << "ec=" << ec << std::endl;
            socket.close();
          } else {
            std::cout << "Read ec=" << ec << " sz=" << sz << std::endl;
            // std::cout << xt << std::endl;

            listener.onTrade(t);
            do_read(listener);
          }
        });
  };

  void run(sink_type &listener) {
    boost::asio::async_connect(
        socket, endpoints,
        [this, &listener](const errcode &ec, tcp::endpoint ep) {
          if (ec) {
            std::cout << "Error code " << ec << std::endl;
            return;
          };
          std::cout << "Connected" << std::endl;
          do_read(listener);
        });
    ios.run();
  };
};
