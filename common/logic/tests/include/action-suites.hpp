#include <gmock/gmock.h>

#include "effect-suites.hpp"

#include "Activatable.hpp"
#include "Buff.hpp"
#include "Damage.hpp"
#include "CharacterInstance.hpp"
#include "GameState.hpp"
#include "TurnOrder.hpp"

namespace DnD {
class ActionSuite : public DamageSuite{
 protected:
    NPC test_enemy_;
    Storage<Location> locations;
    Action action;
    Storage<PlayerCharacter> players_;
    MockDice* dice_ptr;

 public:
    ActionSuite() :
        DamageSuite(),
        locations(),
        action(AreaFactory::create(1, 1), {}, Action::Target::Enemies, 2),
        dice_ptr(dice.get())
    {
        locations.add(0, "", 0, 5, 5);
        action.addEffect(std::make_unique<DealDamage>(DamageType(1), 4, 2, std::move(dice)));
        action.addEffect(std::make_unique<Move>(1, 2));
        action.addEffect(std::make_unique<Buff>(StatBased::Stats{ {"str", -2}, {"dex", -1} }, 2));

        test_enemy_.setStat("str", 10);
        test_enemy_.setStat("dex", 14);

        auto& location = locations.get(0);

        // Add hostile enemies
        for (size_t i = 0; i < 5; ++i) {
            location.npc().add(i, test_enemy_, PositionFactory::create(Tile{i, 1}), map, true);
        }
        location.npc().add(5, test_enemy_, PositionFactory::create(Tile{2, 0}), map, true);

        using ::testing::ReturnRef;

        EXPECT_CALL(map, currentLocation())
            .WillRepeatedly(ReturnRef(location));

        EXPECT_CALL(map, locations())
            .WillRepeatedly(ReturnRef(locations));

        EXPECT_CALL(map, players())
            .WillRepeatedly(ReturnRef(players_));
    }
};

class ActivatableSuite : public ActionSuite {
 protected:
    Action heal_action;

 public:
    ActivatableSuite() :
        ActionSuite(),
        heal_action(AreaFactory::create(), {}, Action::Target::Allies, 0, Action::Cast::Self, false)
    {   
        players_.add(8, char_template_, PositionFactory::create(Tile{2, 2}), map, Class(), Race());

        heal_action.addEffect(std::make_unique<Heal>(3));
        char_template_.setMaxHP(10);

        test_enemy_.setMaxHP(10);
        for (auto& [_, enemy] : locations.get(0).npc()) {
            enemy.resetHP();
        }
    }
};
}  // namespace DnD