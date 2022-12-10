#pragma once

#include <boost/asio.hpp>

using executor_t = std::function<void()>;

class EventLoop {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void schedule (executor_t) = 0;
};

class BoostEventLoop: public EventLoop {
private:
    boost::asio::io_context context;

public:
    virtual void start() override;
    virtual void stop() override;
    virtual void schedule(executor_t) override;

    boost::asio::io_context &get_asio_context();
};
