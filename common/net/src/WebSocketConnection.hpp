#pragma once

#include <WebSocketStream.hpp>
#include <Buffer.hpp>

class WebSocketConnection {
private:
    WebSocketStream *ws;
    Buffer *buffer;

public:
    WebSocketConnection ();
    ~WebSocketConnection();

    void async_read (handler_t);
    void async_write (std::string, handler_t);

    bool is_stopped();

    void open();
    void close();
};

class BoostWebSocketConnection: public WebSocketConnection {
private:
    BoostWebSocketStream *ws;
    BoostBuffer *buffer;

public:
    BoostWebSocketConnection();
    ~BoostWebSocketConnection();

    void async_read (handler_t);
    void async_write (std::string, handler_t);

    bool is_stopped();

    void open();
    void close();
};

class RecievingConnection: public WebSocketConnection {
public:
    RecievingConnection ();

    void recieve();
    virtual void on_recieve(const ErrorCode &ec) = 0;
};
