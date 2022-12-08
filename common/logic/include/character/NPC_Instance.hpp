#pragma once

#include "CharacterInstance.hpp"
#include "NPC.hpp"

namespace DnD {
class NPC_Instance : public CharacterInstance {
 private:
    bool is_hostile_;

 public:
    NPC_Instance(size_t id, NPC& original, std::unique_ptr<Position>&& pos,
                 GameMap& map, bool is_hostile = false, int money = 100, Storage<Item*> items = {});

    std::tuple<Activatable::Result, ErrorStatus>
        use(std::string_view action_type, size_t action_id,
                       const std::vector<Tile>& target, const DiceInterface* dice = nullptr) override {
        return CharacterInstance::use(action_type, action_id, target, dice);
    }

    bool isHostile() const {
        return is_hostile_;
    }

    void makeHostile() {
        is_hostile_ = true;
    }

    void makeFriendly() {
        is_hostile_ = false;
    }

    void setLocation(Location& loc) override;
};
}  // namespace DnD
