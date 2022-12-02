#include <gmock/gmock.h>

#include "mocks.hpp"

#include "GameState.hpp"
#include "TurnOrder.hpp"

using ::testing::ReturnRef;
using ::testing::SizeIs;

namespace DnD {
class TurnOrderSuite : public ::testing::Test {
 protected:
    MockGameMap map;
    Location location;
    GameStateImpl game;
    TurnOrder queue;

    NPC enemy;
    Character player_template;
    Class char_class_;

 public:
    TurnOrderSuite() : map(), location(), game(&map), queue(game, map) {
        for (size_t i = 0; i < 2; ++i) {
            location.npc().add(i, enemy, PositionFactory::create({i, i}), map);
        }
        game.players().add(2, player_template, PositionFactory::create({1, 2}), map, char_class_, Race());
    }
};

TEST_F(TurnOrderSuite, BuffsDissapear) {  // cppcheck-suppress [syntaxError]
    EXPECT_CALL(map, currentLocation())
        .WillRepeatedly(ReturnRef(location));

    StatBased::Stats buff_base = {{"str", 2}};

    queue.fillQueue();
    ASSERT_THAT(queue, SizeIs(3));

    location.npc().each([&] (auto& npc) { npc.addBuff({buff_base, 1}); });
    game.players().each([&] (auto& player) { player.addBuff({buff_base, 2}); });

    PlayerCharacter& player = game.players().get(2);

    location.npc().each([&] (auto& npc) {
        ASSERT_THAT(npc.buffs(), SizeIs(1));
        ASSERT_EQ(npc.buffs().front().turnsLeft(), 1);
    });

    ASSERT_THAT(player.buffs(), SizeIs(1));
    ASSERT_EQ(player.buffs().front().turnsLeft(), 2);

    // First entry should be the only player, with id == 2
    ASSERT_EQ(queue.getActiveCharacter(), &player);

    // Skip to the player's turn, check his buff
    queue.skipTurns(3);
    ASSERT_EQ(player.buffs().front().turnsLeft(), 1);

    // Skip to the enemy's turn, check that his buff has expired
    queue.nextTurn();
    ASSERT_THAT(location.npc().get(0).buffs(), SizeIs(0));

    // While second enemy still has the buff
    NPC_Instance& npc = location.npc().get(1);
    ASSERT_EQ(queue.getActiveCharacter(), &npc);
    ASSERT_THAT(npc.buffs(), SizeIs(1));
    ASSERT_EQ(npc.buffs().front().turnsLeft(), 1);
}

TEST_F(TurnOrderSuite, SkillsColldown) {
    PlayerCharacter& player = game.players().get(2);
    Skill skill(0, "", 0, {}, 2, 3);

    player.skills().add(skill);

    auto& player_skill = player.skills().get(0);

    ASSERT_EQ(player_skill.turnsLeft(), 0);
    auto [results, status] = player.use("skill", 0, {});
    ASSERT_TRUE(status.ok());

    ASSERT_EQ(player_skill.turnsLeft(), player_skill.original().cooldown());
    player.use("skill", 0, {});
    ASSERT_FALSE(status.ok());

    queue.skipTurns(3);
    ASSERT_EQ(player_skill.turnsLeft(), player_skill.original().cooldown() - 1);

    queue.skipTurns(3);
    ASSERT_EQ(player_skill.turnsLeft(), 0);
}
}  // namespace DnD
