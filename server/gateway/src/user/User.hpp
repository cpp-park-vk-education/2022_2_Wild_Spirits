#pragma once

#include <string>
#include <memory>

#include <UserConnection.hpp>
// #include <Room.hpp>

class User {
private:
    std::string nickname;
    std::weak_ptr<UserConnection> connection;
    // Room *room;
    std::size_t _id;

public:
    User (const std::string &nickname, std::size_t id): nickname(nickname), _id(id) {}

    std::size_t id() const {
        return _id;
    }
    // void connectToRoom (Room*);
    void linkConnection(std::shared_ptr<UserConnection> user_connection) {
        connection = user_connection;
    }
};
