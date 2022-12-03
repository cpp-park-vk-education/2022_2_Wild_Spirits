#pragma once
#include <unordered_map>
#include "RoomProcessorEngine.hpp"

class PlayerCharacters{
private:
    std::unordered_map<unsigned int, std::string> player_table;
public:
    PlayerCharacters();
    std::string getPlayerName(unsigned int id);
    unsigned int getUserId(std::string player_name);
    
};



class RoomSideProcessor{
private:
    RoomProcessorEngine engine;
    PlayerCharacters players;
    Room::GameLogicProcessor& room;

    bool sendDM(string request_string);
    bool sendInstance(unsigned int user_id);
    bool broadcast(string request_string);
public:
    RoomSideProcessor();
};