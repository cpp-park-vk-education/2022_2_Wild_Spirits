#include <UserConnectionImpl.hpp>

#include <iostream>

#include <ImageStorage.hpp>
#include <Encoder.hpp>

void UserConnectionImpl::sendMessage(std::string message) {
    connection->async_write(message, [](){
        return;
    });
}

void UserConnectionImpl::on_recieve(std::string message) {
    processRequest(message);
    recieve();
}

void UserConnectionImpl::processRequest(std::string request) {
    user.getRoom()->processRequest(user.id(), request);
}