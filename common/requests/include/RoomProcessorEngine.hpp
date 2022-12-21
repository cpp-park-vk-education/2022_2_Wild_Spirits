#pragma once

#include "RequestStringGenerator.hpp"
#include "StringRequestParser.hpp"
#include "ChangeCollector.hpp"
#include "nlohmann/json.hpp"
#include "ChangeGetter.hpp"



class RoomProcessorEngine{
private:
    RequestStringGenerator generator;
    RoomRequestStringParser parser;
    DnD::LogicProcessor &game_state;
    ChangeCollector collector;
    ChangeGetter change_getter;
public:
    RoomProcessorEngine(DnD::LogicProcessor &gameState);
    nlohmann::json parse(string request);
    nlohmann::json getChanges(nlohmann::json request_object);
    RoomProcessorEngine() = delete;
};