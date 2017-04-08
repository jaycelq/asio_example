//
// Created by Li Qiang on 08/04/2017.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class printer
{
public:
    printer(boost::asio::io_service &io) : timer_(io, boost::posix_time::seconds(1)), count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print, this));
    }
    ~printer()
    {
        std::cout << "Finish Print: tick " << count_;
    }

    void print()
    {
        if (count_ < 5)
        {
            count_++;
            std::cout << "Tick " << count_ << std::endl;
            timer_.expires_from_now(boost::posix_time::seconds(1));
            timer_.async_wait(boost::bind(&printer::print, this));
        }
    }
private:
    boost::asio::deadline_timer timer_;
    uint32_t count_;
};

int main()
{
    boost::asio::io_service io;
    printer p(io);

    io.run();

    return 0;
}