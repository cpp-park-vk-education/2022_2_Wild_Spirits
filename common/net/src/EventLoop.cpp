#include <EventLoop.hpp>

void BoostEventLoop::start() {
    context.run();
}

void BoostEventLoop::stop() {
    context.stop();
}

boost::asio::io_context &BoostEventLoop::get_asio_context() {
    return context;
}

void BoostEventLoop::schedule(executor_t executor) {
    boost::asio::post(context, executor);
}
