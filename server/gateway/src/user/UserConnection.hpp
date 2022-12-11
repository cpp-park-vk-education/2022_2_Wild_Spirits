#pragma once

#include <User.hpp>
#include <iostream>

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
    virtual void processRequest(std::string request) = 0;

    // virtual void connectToRoom(std::string room_name) = 0;
};