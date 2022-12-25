#pragma once

#include <functional>
#include <algorithm>
#include <unordered_map>
#include <string>

#include <RoomManager.hpp>
#include <UserConnection.hpp>

class RoomConnector {
protected:
    RoomManager &room_manager;

    using connection_t = std::shared_ptr<UserConnection>;
    using connection_handler_t = std::function<void(connection_t)>;

    void onError(const std::string &error_msg, connection_t, connection_handler_t);
    void onWrongFormat(connection_t, connection_handler_t);
    void onWrongRoomId(std::size_t room_id, connection_t, connection_handler_t);

    void onConnect(std::size_t room_id, connection_t, connection_handler_t);
    void onCreate(std::size_t room_id, connection_t, connection_handler_t);
    void onPermissionDenied(connection_t, connection_handler_t);

public:
    explicit RoomConnector(RoomManager &room_manager);

    void processRequest(connection_t, connection_handler_t);

    virtual void createRoom(connection_t, connection_handler_t) = 0;
    virtual void connectToRoom(std::size_t room_id, connection_t, connection_handler_t) = 0;
    virtual void listRooms(connection_t, connection_handler_t) = 0;
};

struct RoomRecord {
    std::size_t id;
    std::size_t dm_id;

    RoomRecord(std::size_t id, std::size_t dm_id): id(id), dm_id(dm_id) {}
};

class InMemoryRoomConnector: public RoomConnector {
private:
    std::unordered_map<int, RoomRecord> room_base;

public:
    explicit InMemoryRoomConnector(RoomManager &room_manager): RoomConnector(room_manager) {}

    virtual void createRoom(connection_t, connection_handler_t) override;
    virtual void connectToRoom(std::size_t room_id, connection_t, connection_handler_t) override;
    virtual void listRooms(connection_t, connection_handler_t) override;
};
