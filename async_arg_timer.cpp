//
// Created by Li Qiang on 08/04/2017.
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

void print(const boost::system::error_code &ec, int &count, boost::asio::deadline_timer &timer)
{
    if (count < 5)
    {
        count++;
        std::cout << "Tick: " << count << "s" << std::endl;

        timer.expires_from_now(boost::posix_time::seconds(1));
        timer.async_wait(boost::bind(print, boost::asio::placeholders::error, count, std::ref(timer)));
    }
}

int main()
{
    boost::asio::io_service io;

    boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));

    int count = 0;
    timer.async_wait(boost::bind(print, boost::asio::placeholders::error, count, std::ref(timer)));

    io.run();

    return 0;
}
