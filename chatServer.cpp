#include "pretty_printer.hpp"
#include <array>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <set>
#include <utility>

using boost::asio::ip::tcp;

using ArrayType = std::vector<char>;
using ArrayPtr = std::shared_ptr<ArrayType>;
// using CbType = std::function<void(ArrayPtr)>;

class server;
// template<typename T>
// struct TD;

template <typename SessionType>
class Handler
{
    using SessionPtr = std::shared_ptr<SessionType>;

    std::set<SessionPtr> sessions;

public:
    void insertSession(SessionPtr ptr) { sessions.insert(ptr); }

    void removeSession(SessionPtr ptr)
    {
        auto sz = sessions.erase(ptr);
        std::cout << "Removed " << sz << "\n";
    }

    void do_write(ArrayPtr ary, SessionPtr sender)
    {
        // auto self(shared_from_this());
        for (auto& session : sessions) {
            if (sender != session) {
                boost::asio::async_write(
                    session->socket_, boost::asio::buffer(ary->data(), ary->size()),
                    [this, ary, session](boost::system::error_code ec,
                                         std::size_t length) {
                        std::cout << "Wrote " << length << " of " << ary->size()
                                  << std::endl;
                        if (!ec) {
                            // do_read();
                        } else {
                            std::cout << "Error writing!!!\n";
                            // Hopefully by the time this gets called the iterator is
                            // already
                            // dead.
                            removeSession(session);
                        };
                    });
            }
        }
    }
};

class session : public std::enable_shared_from_this<session>
{
public:
    tcp::socket socket_;

    using HandlerType = Handler<session>;

    session(tcp::socket socket) : socket_(std::move(socket))
    {
        memset(data_, 0, sizeof(data_));
    }

    void start(HandlerType& handler) { do_read(handler); }

private:
    void do_read(HandlerType& handler)
    {
        std::cout << "Do_read" << std::endl;
        const auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                                [this, self, &handler](boost::system::error_code ec,
                                                       std::size_t length) {
                                    std::cout << "Got some data" << std::endl;
                                    ArrayPtr tmpBuf = std::make_shared<ArrayType>(
                                        data_, data_ + length);
                                    print(std::cout, tmpBuf->data());
                                    if (!ec) {
                                        std::cout << "Calling with ";
                                        print(std::cout, tmpBuf->data());
                                        handler.do_write(tmpBuf, self);
                                        do_read(handler);
                                    }
                                });
    }

    enum { max_length = 1024 };
    char data_[max_length];
};

template <typename T>
struct TD;

class server
{
    Handler<session> handler;

public:
    server(boost::asio::io_service& io_service, short port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
          socket_(io_service)
    {
        do_accept();
    }

private:
    void do_accept()
    {
        std::cout << "Accepted" << std::endl;
        acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                auto ptr = std::make_shared<session>(std::move(socket_));
                handler.insertSession(ptr);
                ptr->start(handler);
            }
            do_accept();
        });
    }
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }
        boost::asio::io_service io_service;
        server s(io_service, std::atoi(argv[1]));
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
