#pragma once

#include <string>
#include <WebSocketConnection.hpp>

class ClientConnection: public RecievingConnection {
public:
    virtual void sendRequest (std::string request, handler_t handler) = 0;
    virtual void getImage (std::string path, handler_t handler) = 0;
};

class ClientConnectionImpl: public ClientConnection {
public:
    virtual void on_recieve (const ErrorCode &ec) override;
    virtual void sendRequest (std::string request, handler_t handler) override;
    virtual void getImage (std::string path, handler_t handler) override;
};
