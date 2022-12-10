#include <WebSocketConnection.hpp>

BoostWebSocketConnection::BoostWebSocketConnection(ws_ptr_t ws, buffer_ptr_t buffer):
    ws(std::move(ws)), buffer(buffer) {}

void BoostWebSocketConnection::clearBuffer() {
    buffer->clear();
}

void BoostWebSocketConnection::async_read(read_handlter_t handler) {
    ws->async_read(*buffer, [handler, this](beast::error_code ec, std::size_t bytes_read) {
        if (ec == beast::websocket::error::closed) {
            return;
        }
        std::string message = buffer->data();
        clearBuffer();
        handler(message);
    });
}

void BoostWebSocketConnection::async_write(std::string message, handler_t handler) {
    ws->async_write(BoostBuffer(message), [this, handler](beast::error_code ec, std::size_t bytes) {
        if (ec == beast::websocket::error::closed) {
            return;
        }

        handler(ec, bytes);
    });
}

RecievingConnection::RecievingConnection(std::shared_ptr<WebSocketConnection> connection):
    connection(std::move(connection)) {}

void RecievingConnection::recieve() {
    connection->async_read(beast::bind_front_handler(&RecievingConnection::on_recieve, shared_from_this()));
}
