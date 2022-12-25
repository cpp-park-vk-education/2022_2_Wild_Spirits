#pragma once

#include <Room.hpp>

class RoomImpl: public Room {
private:
    std::vector<User*> players;
    User* DM;

    User *getUserById(std::size_t id);

public:
    RoomImpl (User*, std::size_t, Gateway&);

    virtual void addUser(User*) override;

    virtual void sendUser(std::size_t user_id, const std::string&) override;
    virtual void sendDM(const std::string&) override;
    virtual void broadcast(const std::string&) override;

    virtual void processRequest(std::size_t user_id, const std::string &request) override;
};
