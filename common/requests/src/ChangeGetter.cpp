#include "ChangeGetter.hpp"

void ChangeGetter::load_collector(change_queue changes){

}

ChangeGetter::ChangeGetter(ChangeCollector &collector, Room::GameLogicProcessor &gameState)
        : game_state(gameState), collector(collector) {

}

void ChangeGetter::load_collector(string change) {

}

