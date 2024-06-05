#pragma once

#include <boost/asio.hpp>
#include <ctime>
#include <iostream>
#include <string>

#include "trade.h"
#include <utility>

// TODO - circular array
// TODO - have this use a 'proper' buffer. Not just consume one element at a
// time!

#include <deque>

using boost::asio::ip::tcp;
using socket_type = boost::asio::ip::tcp::socket;
using errcode = boost::system::error_code;
using ios_type = boost::asio::io_service;
using endpoints_type =
    boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>;

// template<typename T>
// struct TD;

// TD<socket_type> sock;

socket_type s(ios_type());

template <typename listener_type> struct trade_client {
  listener_type listener;
  ios_type ios;
  socket_type socket;

  std::deque<Trade> trades;
  uint32_t count;

  trade_client(trade_client &&rhs)
      : listener(std::move(rhs.listener)), ios{}, socket{ios}, trades{},
        count{} {
    std::cout << "Tradecient move ctor" << std::endl;
  };

  trade_client(listener_type &&l)
      : listener(std::move(l)), ios{}, socket{ios}, trades{}, count{} {
    std::cout << "Trade client ctor" << std::endl;
  };

  void do_read() { // TODO - can I provide 'this' as
    // Trade t;
    trades.emplace_back();
    boost::asio::async_read(
        socket, boost::asio::buffer(&trades.back(), sizeof(Trade)),
        [this](const errcode &ec, std::size_t sz) {
          if (ec || sz != sizeof(Trade)) {
            std::cout << "ec=" << ec << std::endl;
            socket.close();
          } else {
            std::cout << "Read ec=" << ec << " sz=" << sz << std::endl;
            // Trade t { trades.pop_front() };
            std::cout << trades.front() << std::endl;
            listener.call(std::forward<Trade &>(trades.front()));
            trades.pop_front();
            do_read();
          }
        });
  };

  void run() {
    ios_type ios{};
    tcp::resolver resolver{ios};
    endpoints_type endpoints{resolver.resolve("localhost", "9876")};
    // socket_type socket { ios };

    socket = socket_type{ios};

    boost::asio::async_connect(
        socket, endpoints, [this](const errcode &ec, tcp::endpoint ep) {
          if (ec) {
            std::cout << "Error code " << ec << std::endl;
            return;
          };
          std::cout << "Connected" << std::endl;
          do_read();
        });
    ios.run();
  }
};
