#include <User.hpp>
#include <UserConnection.hpp>

std::size_t User::id() const {
    return _id;
}

void User::setRoom(Room *room) {
    this->room = room;
}

void User::connectToRoom(Room *room) {
    setRoom(room);
    room->addUser(this);
}

void User::linkConnection(std::shared_ptr<UserConnection> user_connection) {
    connection = user_connection;
}

std::weak_ptr<UserConnection> User::getConnection() {
    return connection;
}

Room *User::getRoom() {
    return room;
}

void User::sendMessage(std::string message) {
    if (!connection.expired())
        connection.lock()->sendMessage(message);
}

void User::leaveRoom() {
    room = nullptr;
}
