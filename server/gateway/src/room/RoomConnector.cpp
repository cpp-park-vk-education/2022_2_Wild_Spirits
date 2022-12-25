#include <RoomConnector.hpp>

RoomConnector::RoomConnector(RoomManager &room_manager):
    room_manager(room_manager) {}

void RoomConnector::processRequest(connection_t connection, connection_handler_t handler) {
    if (connection->get_user().getRoom() != nullptr) {
        std::cout << "already in room" << std::endl;
        handler(connection);
        return;
    }

    connection->async_read([this, connection, handler](std::string message) {
        if (message == "list_rooms") {
            listRooms(connection, handler);
            return;
        }

        if (message == "create") {
            createRoom(connection, handler);
            return;
        }

        std::size_t delimiter_pos = message.find(':');

        if (delimiter_pos == std::string::npos || delimiter_pos == message.size() - 1) {
            onWrongFormat(connection, handler);
            return;
        }

        std::string request = message.substr(0, delimiter_pos);

        if (request != "connect") {
            onWrongFormat(connection, handler);
            return;
        }

        std::string room_name = message.substr(delimiter_pos + 1);

        if (!std::all_of(room_name.begin(), room_name.end(), ::isdigit)) {
            onWrongFormat(connection, handler);
            return;
        }

        connectToRoom(std::stoi(room_name), connection, handler);
    });
}

void RoomConnector::onError(const std::string &error_msg, connection_t connection, connection_handler_t handler) {
    connection->async_write(error_msg,
        [this, connection, handler](bool status){
            processRequest(connection, handler);
    });
}

void RoomConnector::onWrongFormat(connection_t connection, connection_handler_t handler) {
    onError("Room connection error: wrong format", connection, handler);
}

void RoomConnector::onWrongRoomId(std::size_t room_id, connection_t connection, connection_handler_t handler) {
    onError("Room with id " + std::to_string(room_id) + " does not exist", connection, handler);
}

void RoomConnector::onPermissionDenied(connection_t connection, connection_handler_t handler) {
    onError("Permission denied", connection, handler);
}

void RoomConnector::onConnect(std::size_t room_id, connection_t connection, connection_handler_t handler) {
    connection->async_write("connected to room with id:" + std::to_string(room_id),
                            [connection, handler](bool status){
                                handler(connection);
                            });
}

void RoomConnector::onCreate(std::size_t room_id, connection_t connection, connection_handler_t handler) {
    connection->async_write("room_id:" + std::to_string(room_id), [connection, handler](bool status){
        handler(connection);
    });
}

void InMemoryRoomConnector::createRoom(connection_t connection, connection_handler_t handler) {
    User *dm = &connection->get_user();
    Room &room = room_manager.createRoom(dm);

    room_base.emplace(room.id(), RoomRecord(room.id(), dm->id()));

    dm->setRoom(&room);

    onCreate(room.id(), connection, handler);
}

void InMemoryRoomConnector::connectToRoom(std::size_t room_id,
                                  connection_t connection,
                                  connection_handler_t handler) {
    if (room_manager.contains(room_id)) {
        Room &room = room_manager.get(room_id);
        connection->get_user().connectToRoom(&room);

        onConnect(room_id, connection, handler);
    } else if (room_base.contains(room_id)) {
        auto record = room_base.find(room_id)->second;
        User *dm = &connection->get_user();

        if (record.dm_id == dm->id()) {
            Room &room = room_manager.createRoom(room_id, dm);

            dm->setRoom(&room);
            onCreate(room_id, connection, handler);
        } else {
            onPermissionDenied(connection, handler);
        }
    } else {
        onWrongRoomId(room_id, connection, handler);
    }
}

void InMemoryRoomConnector::listRooms(connection_t connection, connection_handler_t handler) {
    User *dm = &connection->get_user();

    std::stringstream ss;

    for (auto &[room_id, room]: room_base) {
        if (dm->id() == room.dm_id) {
            ss << room.id << ",";
        }
    }

    std::string rooms = ss.str();

    connection->async_write("room_ids:[" + rooms.substr(0, rooms.length() - 1) + "]",
                        [connection, handler](bool status){
                            handler(connection);
                        });
}
