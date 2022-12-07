#pragma once

#include "room_interfaces.hpp"
#include "ChangeCollector.hpp"
#include <deque>
#include <tuple>

typedef std::deque<std::tuple<string, string>> change_queue;

class ChangeGetter{
private:
    Room::GameLogicProcessor& game_state;
    ChangeCollector& collector;
    change_queue changes_queue;
    void load_collector(change_queue changes);

public:
    ChangeGetter(ChangeCollector &collector, Room::GameLogicProcessor &gameState);

    void load_collector(string change);
};