#pragma once

#include "client_interfaces.hpp"
#include <tuple>
#include <string>
#include "nlohmann/json.hpp"

using nlohmann::json;


class GameStateChanger{
private:
    Client::GameState &gamestate;

public:
    GameStateChanger(Client::GameState &gamestate);
    bool makechange(std::tuple<std::string, std::string> setter_params);

};



std::unordered_map<> setters_table{
        {""}
};