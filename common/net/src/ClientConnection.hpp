#pragma once

#include <string>
#include <functional>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>

#include <EventLoop.hpp>
#include <WebSocketConnection.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class ClientConnection: public RecievingConnection {
protected:
    using recieve_handler_t = std::function<void(std::string)>;

    recieve_handler_t recieve_handler;
public:
    ClientConnection(connection_ptr_t connection, recieve_handler_t handler):
        RecievingConnection(std::move(connection)), recieve_handler(handler) {}


    // virtual void on_

    // virtual void sendRequest (std::string request, handler_t handler) = 0;
    // virtual void getImage (std::string path, handler_t handler) = 0;
};

class ClientConnectionImpl: public ClientConnection {
private:
    virtual void on_recieve (std::string) override;
public:
    ClientConnectionImpl(connection_ptr_t connection, recieve_handler_t handler):
        ClientConnection(std::move(connection), handler) {}

     static std::shared_ptr<ClientConnection> createConnection(const std::string &address_str,
                                                               u_int16_t port,
                                                               BoostEventLoop&,
                                                               recieve_handler_t);

    // virtual void sendRequest (std::string request, handler_t handler) override;
    // virtual void getImage (std::string path, handler_t handler) override;
};
