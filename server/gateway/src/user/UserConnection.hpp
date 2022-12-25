#pragma once

#include <User.hpp>
#include <iostream>
#include <memory>

#include <WebSocketConnection.hpp>
#include <EventLoop.hpp>
// #include <Image.hpp>

class UserConnection: public RecievingConnection {
protected:
    User &user;

public:
    UserConnection(connection_ptr_t connection, User &user):
        RecievingConnection(std::move(connection)), user(user) {
            std::cout << "new connection" << std::endl;
        }

    virtual ~UserConnection() {
        std::cout << "connection deleted" << std::endl;
    }

    User &get_user() {
        return user;
    }

    virtual void sendMessage(std::string message) = 0;
    virtual bool processRequest(std::string request) = 0;

    std::shared_ptr<UserConnection> shared_from_this() {
        return std::dynamic_pointer_cast<UserConnection>(RecievingConnection::shared_from_this());
    }
};
