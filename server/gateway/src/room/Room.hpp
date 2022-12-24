#pragma once

#include <memory>
#include <string>
#include <vector>

class Gateway;

class User;

#ifdef BUILD_LOGIC
    #include <GameState.hpp>
    #include <RoomRequestProcessor.hpp>
    #include <Demo.hpp>
#else
namespace DnD {
    class LogicProcessor {

    };

    class DemoLogicProcessor: public LogicProcessor {

    };

    class GameMap {

    };

    class DemoGameMap: public GameMap {
    public:
        explicit DemoGameMap(LogicProcessor &p) {}
    };
};

class Room;

class RoomSideProcessor {
private:
    int a = -1;
public:
    RoomSideProcessor(Room &room, DnD::LogicProcessor &p, DnD::GameMap &g) {}
    bool acceptRequest(const std::string &request_string) {
        return a++ == 0;
    }
};
#endif

class Room {
protected:
    std::size_t _id;

    std::unique_ptr<DnD::LogicProcessor> logic_processor;
    std::unique_ptr<DnD::GameMap> game_map;

    std::unique_ptr<RoomSideProcessor> processor;
    // RoomSideProcessor processor;

public:
    Gateway &gateway;

    Room(std::size_t id, Gateway &gateway):
        _id(id), logic_processor(std::make_unique<DnD::DemoLogicProcessor>()),
        game_map(std::make_unique<DnD::DemoGameMap>(*logic_processor)), gateway(gateway) {
            processor = std::make_unique<RoomSideProcessor>(*logic_processor, *game_map);
        }

    void get_linked() {
        processor->link_room_connection(this);
    }

    virtual void addUser(User*) = 0;

    virtual void sendDM(const std::string&) = 0 ;
    virtual void sendUser(std::size_t user_id, const std::string&) = 0;
    virtual void broadcast(const std::string&) = 0;

    std::size_t id() const {
        return _id;
    }

    virtual void processRequest(std::size_t user_id, const std::string &request) = 0;
};
