#include <UserConnectionImpl.hpp>

#include <iostream>

#include <ImageStorage.hpp>
#include <Encoder.hpp>
#include <Gateway.hpp>

void UserConnectionImpl::sendMessage(std::string message) {
    connection->async_write(message, [](bool status){
        return;
    });
}

void UserConnectionImpl::on_recieve(std::string message) {
    if (processRequest(message))
        recieve();
}

bool UserConnectionImpl::processRequest(std::string request) {
    if (request == "!leave") {
        auto &gw = user.getRoom()->gateway;
        user.leaveRoom();
        sendMessage("room left");
        gw.connectToRoom(shared_from_this());
        return false;
    }
    user.getRoom()->processRequest(user.id(), request);
    return true;
}
