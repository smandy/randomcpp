#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <functional>
#include <iostream>

//;; (set-frame-font "Hack 22")
//;; (set-frame-font "Inconsolata 18")
// (set-frame-font "Consolas 14")

using boost::asio::ip::tcp;
using namespace std::placeholders;

struct Session : public std::enable_shared_from_this<Session> {
    tcp::socket socket;
    Session(tcp::socket&& _socket)
        : socket(std::move(_socket))

    {
        std::cout << "Creating session" << std::endl;
    }

    ~Session() { std::cout << "Session is being deleted" << std::endl; };
};

struct Ctx {
    Ctx() : ios{}, acceptor{ios, tcp::endpoint{tcp::v4(), 11000}} {}
    boost::asio::io_service ios;
    tcp::acceptor acceptor;
};

using SessionRP = std::shared_ptr<Session>;
using CtxPtr = std::shared_ptr<Ctx>;

void do_accept(const boost::system::error_code&, CtxPtr ctx,
               SessionRP session)
{
    std::cout << "Accepted the guy" << std::endl;
    std::string resp{"Hello there\n"};
    auto buf = boost::asio::buffer(resp.c_str(), resp.length());
    boost::asio::async_write(
        session->socket, buf, [](boost::system::error_code ec, std::size_t len) {
            std::cout << "Wrote " << len << " ec is " << ec << std::endl;
        });
    auto newSession = std::make_shared<Session>(tcp::socket(ctx->ios));
    ctx->acceptor.async_accept(newSession->socket, [&](const auto& arg) {
        do_accept(arg, ctx, newSession);
    });
}

int main(int, char*[])
{
    auto ctx = std::make_shared<Ctx>();
    {
        // Limit the lifetime of session to ensure cleanup
        auto session = std::make_shared<Session>(tcp::socket(ctx->ios));
        ctx->acceptor.async_accept(session->socket,
                                   std::bind(do_accept, _1, ctx, session));
    }
    ctx->ios.run();
}
