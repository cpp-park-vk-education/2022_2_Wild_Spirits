#pragma once

#include <functional>
#include <memory>

#include <EventLoop.hpp>
#include <UserManager.hpp>
#include <Authorizer.hpp>

using acceptor_handler = std::function<std::shared_ptr<UserConnection>>;

class UserAcceptor {
private:
    EventLoop &loop;
    UserManager &manager;
    UserAuthorizer authorizer;

public:
    UserAcceptor (EventLoop&, UserManager&);

    virtual void accept (acceptor_handler) = 0;
    virtual void on_accept (acceptor_handler) = 0;
};

class AsioAcceptor: public UserAcceptor {
public:
    AsioAcceptor(EventLoop&, UserManager&);

    virtual void accept (acceptor_handler) override;
    virtual void on_accept (acceptor_handler) override;
};
