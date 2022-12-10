#include <WebSocketStream.hpp>

BoostWebSocketStream::BoostWebSocketStream(tcp::socket &&socket): ws(std::move(socket)) {}

void BoostWebSocketStream::async_accept_handshake(handshake_handler_t handler) {
    ws.async_accept(handler);
}

void BoostWebSocketStream::async_read(BoostBuffer &buffer, handler_t handler) {
    ws.async_read(buffer.get_underlying_buffer(), handler);
}

void BoostWebSocketStream::async_write(const BoostBuffer &buffer, handler_t handler) {
    ws.async_write(buffer.get_underlying_buffer().data(), handler);
}
