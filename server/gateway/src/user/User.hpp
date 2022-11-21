#pragma once

#include <string>
#include <memory>

#include <UserConnection.hpp>
#include <Room.hpp>

class User {
private:
    std::string nickname;
    std::shared_ptr<UserConnection> connection;
    Room *room;
    std::size_t _id;

public:
    User (std::string nickname);

    std::size_t id() const;
    void connectToRoom (Room*);
    void linkConnection (std::shared_ptr<UserConnection>);
};