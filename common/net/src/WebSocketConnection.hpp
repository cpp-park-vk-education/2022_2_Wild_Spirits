#pragma once

#include <memory>

#include <WebSocketStream.hpp>
#include <Buffer.hpp>

class WebSocketConnection {
protected:
    using read_handler_t = std::function<void(std::string)>;
    using write_handler_t = std::function<void(bool)>;
    using close_handler_t = std::function<void()>;
public:
    virtual void async_read (read_handler_t) = 0;
    virtual void async_write (std::string, write_handler_t) = 0;
    virtual void close(close_handler_t) = 0;

    virtual bool is_stopped() = 0;
};

class BoostWebSocketConnection: public WebSocketConnection {
private:
    using ws_ptr_t = std::shared_ptr<BoostWebSocketStream>;
    using buffer_ptr_t = std::shared_ptr<BoostBuffer>;

    ws_ptr_t ws;
    buffer_ptr_t read_buffer;
    buffer_ptr_t write_buffer;

public:
    BoostWebSocketConnection(ws_ptr_t ws, buffer_ptr_t read_buffer, buffer_ptr_t write_buffer);

    virtual ~BoostWebSocketConnection() {}

    virtual void async_read(read_handler_t) override;
    virtual void async_write(std::string, write_handler_t) override;

    void clearBuffer();

    virtual void close(close_handler_t handler) override;

    virtual bool is_stopped() override;
};

class RecievingConnection: public std::enable_shared_from_this<RecievingConnection> {
protected:
    using read_handler_t = std::function<void(std::string)>;
    using write_handler_t = std::function<void(bool)>;
    using connection_ptr_t = std::shared_ptr<WebSocketConnection>;
    using close_handler_t = std::function<void()>;

    connection_ptr_t connection;

public:
    RecievingConnection(connection_ptr_t connection);

    void async_read(read_handler_t);
    void async_write(std::string, write_handler_t);

    void recieve();
    virtual void on_recieve(std::string) = 0;

    void close(close_handler_t);
};

