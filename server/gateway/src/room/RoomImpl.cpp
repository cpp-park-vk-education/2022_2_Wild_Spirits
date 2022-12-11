#include <RoomImpl.hpp>
#include <User.hpp>

#include <iostream>

RoomImpl::RoomImpl(User *user, std::size_t id): Room(id), DM(user) {
    players.push_back(user);
}

void RoomImpl::addUser(User *player) {
    players.push_back(player);
}

void RoomImpl::sendDM(const std::string &message) {
    DM->sendMessage(message);
}

void RoomImpl::broadcast(const std::string &message) {
    for (User *player : players) {
        player->sendMessage(message);
    }
}

void RoomImpl::processRequest(std::size_t user_id, const std::string &request) {
    broadcast(request);
}

// void RoomImpl::sendImageTo(const std::string& path, std::size_t user_id) {

// }
