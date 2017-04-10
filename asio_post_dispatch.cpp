//
// Created by Li Qiang on 08/04/2017.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

bool startAFunction()
{
    std::cout << "Enter a non-empty string to run A function" << std::endl;

    std::string input;
    getline(std::cin, input);
    return input.length() == 0 ? false : true;
}

void fB()
{
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    std::cout << boost::this_thread::get_id()
              << " running B function" << std::endl;
}

void fA(boost::asio::io_service& ios)
{
    static int selector = 0;
    std::cout << boost::this_thread::get_id() << "starting A function" << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(3));
    if (++selector % 2)
    {
        std::cout << boost::this_thread::get_id()
                  << " dispatching" << std::endl;
        ios.dispatch(fB);
    }
    else
    {
        std::cout << boost::this_thread::get_id()
                  << " posting" << std::endl;
        ios.post(fB);
    }
    std::cout << boost::this_thread::get_id()
              << " exiting A function" << std::endl;
}

int main()
{
    std::cout << "Main thread: " << boost::this_thread::get_id() << std::endl;

    boost::asio::io_service ios;
    boost::asio::io_service::work work(ios);

    size_t count = 3;
    boost::thread_group threads;
    for (size_t i = 0; i < count; ++i)
    {
        threads.create_thread(boost::bind(&boost::asio::io_service::run, &ios));
    }

    while (startAFunction())
    {
        ios.post(boost::bind(fA, boost::ref(ios)));
    }

    std::cout << "Stopping ASIO I/O Service ..." << std::endl;
    ios.stop();
    threads.join_all();
    std::cout << "All threads terminated" << std::endl;

    return 0;
}