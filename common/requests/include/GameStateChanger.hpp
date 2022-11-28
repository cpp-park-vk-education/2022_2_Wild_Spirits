#pragma once

#include "client_interfaces.hpp"
#include <tuple>
#include <string>

class GameStateChanger{
private:
    Client::GameState &gamestate;

public:
    bool makechange(std::tuple<std::string, std::string>);
};