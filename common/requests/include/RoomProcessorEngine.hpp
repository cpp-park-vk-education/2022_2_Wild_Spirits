#pragma once

#include "RequestStringGenerator.hpp"
#include "StringRequestParser.hpp"
#include "room_interfaces.hpp"
#include "ChangeCollector.hpp"

class RoomProcessorEngine{
private:
    RequestStringGenerator generator;
    RoomRequestStringParser parser;
    Room::GameLogicProcessor &game_state;
    ChangeCollector collector;
public:
    RoomProcessorEngine(Room::GameLogicProcessor &gameState);
    void parse(string request);

    RoomProcessorEngine();
};