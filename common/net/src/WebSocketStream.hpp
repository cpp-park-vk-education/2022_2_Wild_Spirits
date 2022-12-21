#pragma once

#include <functional>
#include <memory>
#include <cstdlib>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <ErrorCode.hpp>
#include <Buffer.hpp>
#include <EventLoop.hpp>

namespace beast = boost::beast;

using tcp = boost::asio::ip::tcp;

using handler_t = std::function<void(beast::error_code, std::size_t)>;
using handshake_handler_t = std::function<void(beast::error_code)>;

class WebSocketStream {
public:
    virtual bool is_closed() = 0;
};

class BoostWebSocketStream: public WebSocketStream {
private:
    using close_handler_t = std::function<void()>;
    using buffer_ptr_t = std::shared_ptr<BoostBuffer>;

    beast::websocket::stream<beast::tcp_stream> ws;
public:

    explicit BoostWebSocketStream (tcp::socket &&);
    explicit BoostWebSocketStream (BoostEventLoop&);

    virtual ~BoostWebSocketStream() {}

    void async_read(BoostBuffer &, handler_t);
    void async_write(buffer_ptr_t, handler_t);
    void async_accept_handshake(handshake_handler_t);

    void handshake(const std::string &address) {
        ws.handshake(address, "/");
    }

    void close(close_handler_t close_handler) {
        ws.async_close(beast::websocket::close_code::normal,
            [close_handler](beast::error_code ec){
                close_handler();
            });
    }

    virtual bool is_closed() override;
};
