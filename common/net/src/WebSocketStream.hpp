#pragma once

#include <functional>
#include <cstdlib>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <ErrorCode.hpp>
#include <Buffer.hpp>

namespace beast = boost::beast;

using tcp = boost::asio::ip::tcp;

using handler_t = std::function<void(const ErrorCode &ec, std::size_t N)>;

class WebSocketStream {
public:
    virtual void async_read(Buffer&, handler_t) = 0;
    virtual void async_write(const Buffer&, handler_t) = 0;

    virtual bool is_stopped() = 0;
};

class BoostWebSocketStream: public WebSocketStream {
private:
    beast::websocket::stream<beast::tcp_stream> ws;

public:
    BoostWebSocketStream (tcp::socket);

    virtual void async_read (Buffer &, handler_t) override;
    virtual void async_write (const Buffer&, handler_t) override;

    virtual bool is_stopped() override;
};
