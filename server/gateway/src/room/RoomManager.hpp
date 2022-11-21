#pragma once

#include <cstdlib>

#include <Room.hpp>

class RoomManager {
private:
    std::vector<Room*> rooms;
    
public:
    std::size_t createRoom();
    void deleteRoom();
    Room *getRoom(std::size_t);

    ~RoomManager();
};
