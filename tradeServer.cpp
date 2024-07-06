#include "tradeServer.h"

#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

trade_server::trade_server(ushort port)
    : ios{}, acceptor{ios, {tcp::v4(), port}},
      filesize{static_cast<uint32_t>(fs::file_size(fs::path("tradedata")))},
      num_objects{static_cast<uint32_t>(filesize / sizeof(Trade))},
      mmap{"tradedata", filesize, O_RDWR, false}, trades{
                                                      reinterpret_cast<Trade*>(
                                                          mmap.get())} {};

void trade_server::serve_socket(socket_type&& socket)
{
    // TODO - this could be made recursive so that it's more of a ping-pong
    // rather than scheduling 20000 writes
    for (int i = 0; i < num_objects; ++i) {
        boost::asio::async_write(socket,
                                 boost::asio::buffer(&trades[i], sizeof(Trade)),
                                 [this, i](const errcode& e, size_t sz) {
                                     if (e) {
                                         std::cout << "Error code " << std::endl;
                                         return;
                                     };

                                     if (sz != sizeof(Trade)) {
                                         std::cout << "Ratty size " << sz << std::endl;
                                         return;
                                     };
                                     std::cout << trades[i] << std::endl;
                                 });
    }
};

void trade_server::do_accept()
{
    std::cout << "do_accept" << std::endl;
    acceptor.async_accept([this](const errcode& e, socket_type socket) {
        if (e) {
            std::cout << "ec=" << e << std::endl;
            return;
        };
        std::cout << "Accepted" << std::endl;
        serve_socket(std::move(socket));
        // std::make_shared<chat_session>(std::move(socket))->start();
        std::cout << "Looping" << std::endl;
        do_accept();
    });
};

void trade_server::run()
{
    do_accept();
    ios.run();
};
