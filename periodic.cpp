#include <boost/asio.hpp>
#include <iostream>
// #include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std::placeholders;

void print(const boost::system::error_code&, boost::asio::deadline_timer& t,
           int count)
{
    std::cout << "Hello, world! " << count << std::endl;
    if (count > 0) {
        --(count);
        t.expires_at(t.expires_at() + boost::posix_time::seconds(1));
        t.async_wait(std::bind(print, _1, std::ref(t), count));
    }
}

int main()
{
    boost::asio::io_service io;

    int count{5};

    boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
    t.async_wait(std::bind(print, _1, std::ref(t), count));
    io.run();
    return 0;
}
