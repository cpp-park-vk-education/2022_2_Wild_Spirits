#include <UserConnection.hpp>

void UserConnection::sendMessage(std::string message) {
    connection->async_write(message, [](beast::error_code _, std::size_t bytes){
        return;
    });
}

void UserConnection::on_recieve(std::string message) {
    recieve();
    sendMessage(message);
}
