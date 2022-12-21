#pragma once

#include <functional>
#include <algorithm>
#include <string>

#include <RoomManager.hpp>
#include <UserConnection.hpp>

class RoomConnector {
private:
    RoomManager &room_manager;

    using connection_t = std::shared_ptr<UserConnection>;
    using connection_handler_t = std::function<void(connection_t)>;

public:
    explicit RoomConnector(RoomManager &room_manager);

    void processRequest(connection_t, connection_handler_t);
    void onWrongFormat(connection_t, connection_handler_t);
    void onWrongRoomId(std::size_t room_id, connection_t, connection_handler_t);

    void createRoom(connection_t, connection_handler_t);
    void connectToRoom(std::size_t room_id, connection_t, connection_handler_t);
};
