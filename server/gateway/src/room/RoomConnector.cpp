#include <RoomConnector.hpp>

#include <iostream>

RoomConnector::RoomConnector(RoomManager &room_manager):
    room_manager(room_manager) {}

void RoomConnector::processRequest(connection_t connection, connection_handler_t handler) {
    connection->async_read([this, connection, handler](std::string message) {

        std::cout << message << std::endl;

        if (message == "create") {
            createRoom(connection, handler);
            return;
        }

        std::size_t delimiter_pos = message.find(':');

        std::cout << delimiter_pos << std::endl;

        if (delimiter_pos == std::string::npos || delimiter_pos == message.size() - 1) {
            onWrongFormat(connection, handler);
            return;
        }

        std::string request = message.substr(0, delimiter_pos);

        std::cout << request << std::endl;

        if (request != "connect") {
            onWrongFormat(connection, handler);
            return;
        }

        std::string room_name = message.substr(delimiter_pos + 1);

        if(!std::all_of(room_name.begin(), room_name.end(), ::isdigit)) {
            onWrongFormat(connection, handler);
            return;
        }

        connectToRoom(std::stoi(room_name), connection, handler);
    });
}

void RoomConnector::createRoom(connection_t connection, connection_handler_t handler) {
    Room &room = room_manager.createRoom(&connection->get_user());
    connection->get_user().setRoom(&room);

    connection->async_write("room_id:" + std::to_string(room.id()), [connection, handler](){
        handler(connection);
    });
}

void RoomConnector::connectToRoom(std::size_t room_id,
                                  connection_t connection,
                                  connection_handler_t handler) {

    if (!room_manager.contains(room_id)) {
        onWrongRoomId(room_id, connection, handler);
        return;
    }

    Room &room = room_manager.get(room_id);
    connection->get_user().connectToRoom(&room);

    connection->async_write("connected to room with id:" + std::to_string(room_id),
                            [connection, handler](){
                                handler(connection);
                            });
}

void RoomConnector::onWrongFormat(connection_t connection, connection_handler_t handler) {
    connection->async_write("Room connection error: wrong format",
        [this, connection, handler](){
            processRequest(connection, handler);
    });
}

void RoomConnector::onWrongRoomId(std::size_t room_id, connection_t connection, connection_handler_t handler) {
    connection->async_write("Room with id " + std::to_string(room_id) + " does not exist",
        [this, connection, handler](){
            processRequest(connection, handler);
    });
}
