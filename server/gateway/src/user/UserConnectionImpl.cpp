#include <UserConnectionImpl.hpp>

void UserConnectionImpl::sendMessage(std::string message) {
    connection->async_write(message, [](){
        return;
    });
}

void UserConnectionImpl::on_recieve(std::string message) {
    recieve();
    processRequest(message);
}

void UserConnectionImpl::processRequest(std::string request) {
    user.getRoom()->processRequest(user.id(), request);
}
