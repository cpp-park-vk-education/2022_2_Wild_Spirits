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
    Location location;
    Action action;
    Storage<PlayerCharacter> players_;

 public:
    ActionSuite() :
        DamageSuite(),
        location(0, "", 0, 5, 5),
        action(AreaFactory::create(1, 1), {
            new DealDamage(1, 4, 2, dice),
            new Move(1, 2),
            new Buff({ {"str", -2}, {"dex", -1} }, 2)}, 2) {
        test_enemy_.setStat("str", 10);
        test_enemy_.setStat("dex", 14);

        for (size_t i = 0; i < 5; ++i) {
            location.npc().add(i, test_enemy_, PositionFactory::create(Tile{1, i}), map);
        }
        location.npc().add(5, test_enemy_, PositionFactory::create(Tile{0, 2}), map);

        using ::testing::ReturnRef;

        EXPECT_CALL(map, currentLocation())
            .WillRepeatedly(ReturnRef(location));

        EXPECT_CALL(map, players())
            .WillRepeatedly(ReturnRef(players_));
    }
};

class ActivatableSuite : public ActionSuite {
 protected:
    PlayerCharacter player;
    Action heal_action;

 public:
    ActivatableSuite() :
        ActionSuite(),
        player(8, char_template_, PositionFactory::create(Tile{2, 2}), map, Class(), Race()),
        heal_action(AreaFactory::create(), { new Heal(3) }, 0, Action::CastType::Self, false) {
            char_template_.setMaxHP(10);
            player.resetHP();
            player.takeDamage(5);

            test_enemy_.setMaxHP(10);
            for (auto& [_, enemy] : location.npc()) {
                enemy.resetHP();
            }
        }
};
}  // namespace DnD