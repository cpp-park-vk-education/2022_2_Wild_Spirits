#pragma once

#include <User.hpp>
#include <RoomImpl.hpp>
#include <Manager.hpp>

class Gateway;

class RoomManager: virtual public Manager<RoomImpl> {
public:
    virtual Room &createRoom(std::size_t id, User *dm) = 0;
    virtual Room &createRoom(User *dm) = 0;
    virtual bool contains(std::size_t id) = 0;
};

class RoomManagerImpl: public RoomManager, ManagerImpl<RoomImpl> {
private:
    Gateway &gateway;

public:
    RoomManagerImpl (Gateway &gateway): gateway(gateway) {}

    virtual Room &createRoom(std::size_t id, User *dm) override {
        entities.emplace(id, RoomImpl(dm, id, gateway));

        return get(id);
    }

    virtual Room &createRoom(User *dm) override {
        std::size_t id = id_assigner.assignId();
        return createRoom(id, dm);
    }

    virtual bool contains(std::size_t id) {
        return entities.contains(id);
    }
};
