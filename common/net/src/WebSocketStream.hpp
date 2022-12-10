#pragma once

#include <functional>
#include <cstdlib>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <ErrorCode.hpp>
#include <Buffer.hpp>

namespace beast = boost::beast;

using tcp = boost::asio::ip::tcp;

using handler_t = std::function<void(beast::error_code, std::size_t)>;
using handshake_handler_t = std::function<void(beast::error_code)>;

class WebSocketStream {
public:
    // virtual bool is_stopped() = 0;
};

class BoostWebSocketStream: public WebSocketStream {
private:
    beast::websocket::stream<beast::tcp_stream> ws;

public:
    explicit BoostWebSocketStream (tcp::socket &&);

    void async_read(BoostBuffer &, handler_t);
    void async_write(const BoostBuffer&, handler_t);
    void async_accept_handshake(handshake_handler_t);

    // virtual bool is_stopped() override;
};
