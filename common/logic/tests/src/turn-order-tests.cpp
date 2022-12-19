#include <gmock/gmock.h>

#include "mocks.hpp"

#include "GameState.hpp"
#include "TurnOrder.hpp"

using ::testing::ReturnRef;
using ::testing::Return;
using ::testing::SizeIs;

namespace DnD {
class TurnOrderSuite : public ::testing::Test {
 protected:
    MockGameMap map;
    Location location;
    GameStateImpl game;
    TurnOrder queue;

    SharedStorage<PlayerCharacter> players;

    std::shared_ptr<NPC> enemy;
    std::shared_ptr<Class> char_class_;

    std::vector<size_t> expected_turn_order_;

 public:
    TurnOrderSuite() :
            map(), location(0, "", 0, 5, 5),
            game(), queue(game, map),
            enemy(std::make_shared<NPC>()),
            char_class_(std::make_shared<Class>()) {
        EXPECT_CALL(map, currentLocation())
            .WillRepeatedly(ReturnRef(location));

        EXPECT_CALL(map, currentLocationId())
            .WillRepeatedly(Return(0));

        EXPECT_CALL(map, players())
            .WillRepeatedly(ReturnRef(players));

        EXPECT_CALL(map, allCharacters())
            .WillRepeatedly(ReturnRef(game.allCharacters()));

        for (size_t i = 0; i < 2; ++i) {
            location.npc().add(i, enemy, PositionFactory::create({i, i}), map);
        }
        map.players().add(2, Character(), PositionFactory::create({1, 2}), map, char_class_, std::make_shared<Race>());

        expected_turn_order_.reserve(3);
        expected_turn_order_.push_back(2);

        for (auto& [id, _] : location.npc()) {   // Initial turn order for npc's is unspecified,
            expected_turn_order_.push_back(id);  // as they are stored in an unordered map
        }                                        // Perhaps I should add sorting by action points, dexterity or smth
    }
};

TEST_F(TurnOrderSuite, BuffsDissapear) {  // cppcheck-suppress [syntaxError]
    Buff buff({{"str", 2}}, 2);

    queue.fillQueue();
    ASSERT_THAT(queue, SizeIs(3));

    location.npc().each([&] (auto& npc) { npc.addBuff(buff); });
    map.players().each([&] (auto& player) { player.addBuff(buff); });

    PlayerCharacter& player = map.players().get(2);

    location.npc().each([&] (auto& npc) {
        ASSERT_THAT(npc.buffs(), SizeIs(1));
        ASSERT_EQ(npc.buffs().front().turnsLeft(), 2);
    });

    ASSERT_THAT(player.buffs(), SizeIs(1));
    ASSERT_EQ(player.buffs().front().turnsLeft(), 2);

    // First entry should be the only player, with id == 2
    EXPECT_EQ(queue.getActiveCharacter().lock().get(), &player);
    EXPECT_EQ(queue.getActiveCharacterId(), 2);

    // Skip to the player's turn, check his buff
    queue.skipTurns(3);
    ASSERT_EQ(player.buffs().front().turnsLeft(), 1);

    // Skip to the enemy's turn, check that player's buff has expired (Buff's counter triggers on turn end)
    queue.nextTurn();
    ASSERT_THAT(player.buffs(), SizeIs(0));

    // Skip to the second enemy's turn, check that first enemy's's buff has expired
    queue.nextTurn();
    EXPECT_THAT(location.npc().get(expected_turn_order_[1]).buffs(), SizeIs(0));

    // While second enemy still has the buff
    NPC_Instance& npc = location.npc().get(expected_turn_order_[2]);
    EXPECT_EQ(queue.getActiveCharacter().lock().get(), &npc);
    ASSERT_THAT(npc.buffs(), SizeIs(1));
    EXPECT_EQ(npc.buffs().front().turnsLeft(), 1);
}

TEST_F(TurnOrderSuite, SkillsColldown) {
    PlayerCharacter& player = map.players().get(2);

    queue.pushFront(player.id());
    auto skill = std::make_shared<Skill>(0, "", 0, std::vector<Action>{}, 2, 3);

    player.skills().add(Skill_Instance(skill));

    auto& player_skill = player.skills().get(0);

    ASSERT_EQ(player_skill.turnsLeft(), 0);
    auto [results, status] = player.use("skill", 0, {});
    ASSERT_EQ(status, ErrorStatus::OK);

    ASSERT_EQ(player_skill.turnsLeft(), player_skill.cooldown());
    std::tie(results, status) = player.use("skill", 0, {});
    ASSERT_EQ(status, ErrorStatus::SKILL_ON_COOLDOWN);

    queue.nextTurn();
    ASSERT_EQ(player_skill.turnsLeft(), player_skill.cooldown() - 1);

    queue.skipTurns(2);
    ASSERT_EQ(player_skill.turnsLeft(), 0);

    Activatable* a = new Weapon();
    delete a;
}
}  // namespace DnD
