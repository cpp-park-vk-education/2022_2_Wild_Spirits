#pragma once

#include <boost/asio.hpp>

class EventLoop {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void schedule() = 0;
};

class BoostEventLoop: EventLoop {
private:
    boost::asio::io_context context;

public:
    virtual void start() override;
    virtual void stop() override;
    virtual void schedule() override;
};
