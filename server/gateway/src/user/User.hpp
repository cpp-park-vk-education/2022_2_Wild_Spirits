#pragma once

#include <string>
#include <memory>

#include <Room.hpp>

class UserConnection;
class User {
private:
    std::string nickname;
    std::weak_ptr<UserConnection> connection;
    Room *room;
    std::size_t _id;

public:
    User (const std::string &nickname, std::size_t id): nickname(nickname), _id(id) {}

    std::size_t id() const;

    void setRoom(Room *room);
    void connectToRoom (Room *room);

    void linkConnection(std::shared_ptr<UserConnection> user_connection);
    std::weak_ptr<UserConnection> getConnection();
    Room *getRoom();
    void sendMessage(std::string message);
};
