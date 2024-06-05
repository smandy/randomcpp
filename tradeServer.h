#pragma once

#include <boost/asio.hpp>

#include "mmapper.h"
#include "trade.h"

using boost::asio::ip::tcp;
using socket_type = boost::asio::ip::tcp::socket;
using errcode = boost::system::error_code;

struct trade_server {
  boost::asio::io_service ios;
  tcp::acceptor acceptor;
  uint32_t filesize;
  uint32_t num_objects;
  argoko::MMapper mmap;
  Trade *trades;

  trade_server(ushort port);

  void serve_socket(socket_type &&socket);

  void do_accept();

  void run();
};
