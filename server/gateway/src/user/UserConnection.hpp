#pragma once

#include <WebSocketConnection.hpp>
#include <EventLoop.hpp>
#include <Image.hpp>

class User;

class UserConnection: public RecievingConnection {
private:
    EventLoop &loop;
    User &user;

public:
    UserConnection(EventLoop&);

    void sendMessage(std::string message);
    void processRequest();
    virtual void on_recieve(const ErrorCode &ec) override;
    void sendImage(Image);
};