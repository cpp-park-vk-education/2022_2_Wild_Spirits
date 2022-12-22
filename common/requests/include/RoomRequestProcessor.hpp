#pragma once
#include <unordered_map>
#include <memory>
#include "RoomProcessorEngine.hpp"
#include "sendaccept.hpp"

// #include <Room.hpp>

class Room;


class PlayerCharacters{
private:
    std::unordered_map<unsigned int, std::string> player_table;
    std::unordered_map<std::string, std::size_t> id_table;
public:
    PlayerCharacters();
    std::string getPlayerName(unsigned int id);
    unsigned int getUserId(std::string player_name);
    
};

class RoomSideProcessor : public RequestAcceptor{
private:
    Room &room_connection;
    RoomProcessorEngine engine;
    PlayerCharacters players;
    DnD::LogicProcessor& room;

    bool sendDM(string request_string);
    bool sendInstance(unsigned int user_id);
    bool broadcast(string request_string);
    bool broadcast();
public:
    bool acceptRequest(std::string request_string) override;
    RoomSideProcessor(Room &room_connection, DnD::LogicProcessor &room);
};
