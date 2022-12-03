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
    GameStateChanger();
    bool makechange(std::tuple<std::string, std::string> setter_params);
};