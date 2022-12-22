#include <RoomImpl.hpp>
#include <User.hpp>
#include <Gateway.hpp>

RoomImpl::RoomImpl(User *user, std::size_t id, Gateway &gateway): Room(id, gateway), DM(user) {
    players.push_back(user);
}

void RoomImpl::addUser(User *player) {
    players.push_back(player);
}

void RoomImpl::sendUser(std::size_t user_id, const std::string &message) {
    for (User *user : players) {
        if (user->id() == user_id) {
            user->sendMessage(message);
            break;
        }
    }
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
    // broadcast(request);

    std::size_t delimiter_pos = request.find(':');

    std::string action = request.substr(0, delimiter_pos);
    std::string content = request.substr(delimiter_pos + 1);

    if (action == "get") {
        auto image = gateway.image_storage.getImage(content);
        if (image)
            sendDM(image->getBase64());
        else
            sendDM("image does not exist");
    } else {
        auto hash = gateway.image_storage.saveImage(content, "png");
        broadcast(hash);
    }
}
