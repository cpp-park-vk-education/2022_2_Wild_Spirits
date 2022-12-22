#pragma once

#include <UserConnection.hpp>

class UserConnectionImpl: public UserConnection {
public:
    UserConnectionImpl(connection_ptr_t connection, User &user):
        UserConnection(connection, user) {}

    virtual void sendMessage(std::string message) override;
    virtual void processRequest(std::string request) override;
    virtual void on_recieve(std::string) override;
};