#pragma once

#include "CharacterInstance.hpp"
#include "NPC.hpp"

namespace DnD {
class NPC_Instance : public CharacterInstance {
 private:
    bool is_hostile_;
    std::shared_ptr<NPC> original_;

 public:
    NPC_Instance(size_t id, const std::shared_ptr<NPC>& original, std::unique_ptr<Position>&& pos,
                 GameMap& map, bool is_hostile = false, int money = 100,
                 const SharedStorage<Item>& items = {});

    NPC_Instance(const NPC_Instance& other) = delete;
    NPC_Instance& operator=(const NPC_Instance& other) = delete;

    NPC_Instance(NPC_Instance&& other);
    NPC_Instance& operator=(NPC_Instance&& other) = delete;

    std::tuple<Activatable::Result, ErrorStatus>
        use(std::string_view action_type, size_t action_id,
                       const std::vector<Tile>& target, const DiceInterface* dice = nullptr) override {
        return CharacterInstance::use(action_type, action_id, target, dice);
    }

    const Character& original() const override {
        return *original_;
    }

    bool isHostile() const override {
        return is_hostile_;
    }

    void makeHostile() {
        is_hostile_ = true;
    }

    void makeFriendly() {
        is_hostile_ = false;
    }
};
}  // namespace DnD
