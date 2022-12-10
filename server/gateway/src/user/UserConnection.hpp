#pragma once

#include <WebSocketConnection.hpp>
#include <EventLoop.hpp>
// #include <Image.hpp>

#include <iostream>

class User;

class UserConnection: public RecievingConnection {
private:
    // EventLoop &loop;
    User &user;

public:
    UserConnection(connection_ptr_t connection, User &user):
        RecievingConnection(std::move(connection)), user(user) {
            std::cout << "new connection" << std::endl;
        }

    ~UserConnection() {
        std::cout << "connection deleted" << std::endl;
    }

    const User &get_user() {
        return user;
    }

    void sendMessage(std::string message);
    void processRequest ();
    virtual void on_recieve(std::string) override;
    // void sendImage (Image);
};