//
// Created by Li Qiang on 09/04/2017.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

class printer
{
public:
    printer(boost::asio::io_service &io) :
            strand_(io),
            timer1_(io, boost::posix_time::seconds(1)),
            timer2_(io, boost::posix_time::seconds(1)),
            count_(0)
    {
        timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
        timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
    }

    void print1()
    {
        if (count_ < 5)
        {
            count_++;
            std::cout << "Timer1: Tick: " << count_ << std::endl;
            timer1_.expires_from_now(boost::posix_time::seconds(1));
            timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
        }
    }

    void print2()
    {
        if (count_ < 5)
        {
            count_++;
            std::cout << "Timer2: Tick: " << count_ << std::endl;
            timer2_.expires_from_now(boost::posix_time::seconds(1));
            timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
        }
    }
private:
    boost::asio::io_service::strand strand_;
    boost::asio::deadline_timer timer1_;
    boost::asio::deadline_timer timer2_;
    uint32_t count_;
};

int main()
{
    boost::asio::io_service io;

    printer p(io);
    boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
    io.run();
    t.join();

    return 0;
}