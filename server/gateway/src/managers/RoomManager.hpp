#pragma once

#include <User.hpp>
#include <RoomImpl.hpp>
#include <Manager.hpp>

class RoomManager: virtual public Manager<RoomImpl> {
public:
    virtual Room &createRoom(User *dm) = 0;
    virtual bool contains(std::size_t id) = 0;
};

class RoomManagerImpl: public RoomManager, ManagerImpl<RoomImpl> {
public:
    virtual Room &createRoom(User *dm) override {
        std::size_t id = id_assigner.assignId();
        entities.emplace(id, RoomImpl(dm, id));

        return get(id);
    }

    virtual bool contains(std::size_t id) {
        return entities.contains(id);
    }
};
