#pragma once

#include <boost/asio.hpp>

#include <functional>
#include <memory>

#include <EventLoop.hpp>
#include <UserManager.hpp>
#include <Authorizer.hpp>

class UserAcceptor {
protected:
    using acceptor_handler = std::function<void(std::shared_ptr<UserConnection>)>;
    UserAuthorizer authorizer;

public:
    UserAcceptor (UserManager &manager): authorizer(manager) {}

    virtual void accept (acceptor_handler) = 0;
};

class AsioAcceptor: public UserAcceptor {
private:
    using ws_ptr_t = std::shared_ptr<BoostWebSocketStream>;
    using tcp = boost::asio::ip::tcp;

    BoostEventLoop &loop;
    tcp::acceptor acceptor;
public:
    AsioAcceptor(UserManager &manager, BoostEventLoop&, tcp::acceptor&&);

    virtual void accept(acceptor_handler) override;
    void on_accept(beast::error_code, tcp::socket, acceptor_handler);
    void on_handshake(ws_ptr_t, beast::error_code, acceptor_handler);
};
