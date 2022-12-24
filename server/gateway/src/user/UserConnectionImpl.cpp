#include <UserConnectionImpl.hpp>

#include <iostream>

#include <ImageStorage.hpp>
#include <Encoder.hpp>

void UserConnectionImpl::sendMessage(std::string message) {
    connection->async_write(message, [](bool status){
        return;
    });
}

void UserConnectionImpl::on_recieve(std::string message) {
    std::cout << "recieved: " << message << std::endl;
    processRequest(message);
    recieve();
}

void UserConnectionImpl::processRequest(std::string request) {
    std::cout << "recieved: " << request << std::endl;
    user.getRoom()->processRequest(user.id(), request);
}
