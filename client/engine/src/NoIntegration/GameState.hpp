#pragma once

#include <memory>
#include <vector>

#include "GameClasses.hpp"

namespace DnD {

    class GameState {
    public:
        // virtual SharedStorage<NPC>& npc() = 0;
        // virtual Storage<CharacterInstance*>& allCharacters() = 0;

        // virtual SharedStorage<Item>& items() = 0;
        // virtual SharedStorage<ActivatableItem>& activatableItems() = 0;
        // virtual SharedStorage<Weapon>& weapons() = 0;
        // virtual SharedStorage<Spell>& spells() = 0;
        // virtual SharedStorage<Armor>& armor() = 0;

        // virtual SharedStorage<Race>& races() = 0;
        // virtual SharedStorage<Class>& classes() = 0;

        // virtual ~GameState() { }

    protected:
    };

    class GameStateImpl : public GameState {
    public:
        GameStateImpl() { TestImages::init(); }

    protected:
    };

}    // namespace DnD
