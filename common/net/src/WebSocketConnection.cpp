#include <WebSocketConnection.hpp>

BoostWebSocketConnection::BoostWebSocketConnection(ws_ptr_t ws, buffer_ptr_t read_buffer, buffer_ptr_t write_buffer):
    ws(std::move(ws)), read_buffer(read_buffer), write_buffer(write_buffer) {}

void BoostWebSocketConnection::clearBuffer() {
    read_buffer->clear();
    write_buffer->clear();
}

#include <iostream>

void BoostWebSocketConnection::async_read(read_handler_t handler) {
    ws->async_read(*read_buffer, [handler, this](beast::error_code ec, std::size_t bytes_read) {
        if (ec == beast::websocket::error::closed || ec == boost::asio::error::eof) {
            return;
        }
        std::string message = read_buffer->data();
        read_buffer->clear();

        handler(message);
    });
}

void BoostWebSocketConnection::async_write(std::string message, write_handler_t handler) {
    write_buffer->setData(message);
    ws->async_write(write_buffer, [this, handler](beast::error_code ec, std::size_t bytes) {
        if (ec == beast::websocket::error::closed) {
            handler(false);
            return;
        }

        write_buffer->clear();
        handler(true);
    });
}

void BoostWebSocketConnection::close(close_handler_t handler) {
    ws->close(handler);
}

bool BoostWebSocketConnection::is_stopped() {
    return ws->is_closed();
}

RecievingConnection::RecievingConnection(connection_ptr_t connection):
    connection(std::move(connection)) {}

void RecievingConnection::recieve() {
    connection->async_read(beast::bind_front_handler(&RecievingConnection::on_recieve, shared_from_this()));
}

void RecievingConnection::async_read(read_handler_t handler) {
    connection->async_read(handler);
}

void RecievingConnection::async_write(std::string message, write_handler_t handler) {
    connection->async_write(message, [handler](bool status){
        handler(status);
    });
}

void RecievingConnection::close(close_handler_t close_handler) {
    connection->close(close_handler);
}
