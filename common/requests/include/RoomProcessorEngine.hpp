#pragma once

#include "RequestStringGenerator.hpp"
#include "StringRequestParser.hpp"
#include "room_interfaces.hpp"
#include "ChangeCollector.hpp"
#include "nlohmann/json.hpp"
#include "ChangeGetter.hpp"



class RoomProcessorEngine{
private:
    RequestStringGenerator generator;
    RoomRequestStringParser parser;
    Room::GameLogicProcessor &game_state;
    ChangeCollector collector;
    ChangeGetter change_getter;
public:
    RoomProcessorEngine(Room::GameLogicProcessor &gameState);
    nlohmann::json parse(string request);
    nlohmann::json getChanges(nlohmann::json request_object);
    RoomProcessorEngine() = delete;
};