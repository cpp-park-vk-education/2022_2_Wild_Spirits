#pragma once

#include "CharacterInstance.hpp"
#include "NPC.hpp"

class NPC_Instance : public CharacterInstance {
 private:
    bool is_hostile_;

 public:
    NPC_Instance(NPC& original, Position* pos, GameMap& map,
                 int money = 100, std::unordered_map<size_t, Item*> items = {}) :
        CharacterInstance(original, pos, map, money, items) {}

    bool isHostile() const {
        return is_hostile_;
    }

    void makeHostile() {
        is_hostile_ = true;
    }

    void makeFriendly() {
        is_hostile_ = false;
    }
};
