#include <RoomImpl.hpp>
#include <User.hpp>
#include <Gateway.hpp>

RoomImpl::RoomImpl(User *user, std::size_t id, Gateway &gateway): Room(id, gateway), DM(user) {
    players.push_back(user);
}

void RoomImpl::addUser(User *player) {
    players.push_back(player);
}

User *RoomImpl::getUserById(std::size_t user_id) {
    for (User *user : players) {
        if (user->id() == user_id) {
            return user;
        }
    }
    return nullptr;
}

void RoomImpl::sendUser(std::size_t user_id, const std::string &message) {
    getUserById(user_id)->sendMessage(message);
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
    processor.acceptRequest(request);
}
