#include <WebSocketStream.hpp>

BoostWebSocketStream::BoostWebSocketStream(tcp::socket &&socket): ws(std::move(socket)) {}
BoostWebSocketStream::BoostWebSocketStream(BoostEventLoop &loop): ws(loop.get_asio_context()) {}

void BoostWebSocketStream::async_accept_handshake(handshake_handler_t handler) {
    ws.async_accept(handler);
}

void BoostWebSocketStream::async_read(BoostBuffer &buffer, handler_t handler) {
    ws.async_read(buffer.get_underlying_buffer(), handler);
}

void BoostWebSocketStream::async_write(buffer_ptr_t buffer, handler_t handler) {
    ws.async_write(buffer->get_underlying_buffer().data(), handler);
}

bool BoostWebSocketStream::is_closed() {
    return !ws.is_open();
}
