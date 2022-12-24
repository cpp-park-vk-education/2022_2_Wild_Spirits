#include "Demo.hpp"

#include "Damage.hpp"
#include "EffectFactory.hpp"

namespace DnD {
    DemoLogicProcessor::DemoLogicProcessor() : LogicProcessorImpl() {
        npc().add(0, "Enemy1", 0, 10, 500, 10, 10, StatBased::defaultStats());

        auto& test_npc = npc().get(0);
        test_npc.setStat("str", 14);
        test_npc.setStat("int", 8);
        test_npc.setStat("wis", 6);

        auto [slashing, _] = damage_types.getDamageType(damage_types.typeId("Slashing"));
        auto [fire, __] = damage_types.getDamageType(damage_types.typeId("Fire"));

        Action damage_action(AreaFactory::create(), {}, Action::Target::Allies, 1);
        damage_action.addEffect(EffectFactory::create(slashing, 6, 1));

        Action damage_player_action(AreaFactory::create(), {}, Action::Target::Enemies, 1);
        damage_player_action.addEffect(EffectFactory::create(fire, 8, 1));

        Action damage_move_action(AreaFactory::create(1, 1), {}, Action::Target::Both, 1);
        damage_move_action.addEffect(EffectFactory::create(slashing, 4, 2));
        damage_move_action.addEffect(EffectFactory::create(1, 2));

        Action heal_action(AreaFactory::create(), {}, Action::Target::Allies);
        heal_action.addEffect(EffectFactory::create(3));

        Action buff_action(AreaFactory::create(1, 1), {}, Action::Target::Allies);
        buff_action.addEffect(EffectFactory::create({{"str", 4}, {"dex", 2}}, 3));

        Action move_action(AreaFactory::create(0, 2), {}, Action::Target::Both, 2);
        move_action.addEffect(EffectFactory::create(0, 2));

        test_npc.baseSkills().add(
            0, "Basic Hit", 0, std::vector<Action>{damage_action}, 3, 1, "str"
        );

        test_npc.baseSkills().add(
            1, "Splash Hit", 0, std::vector<Action>{damage_move_action}, 5, 3, "str"
        );

        activatableItems().add(
            0, "Healing Potion", 0, std::vector<Action>{heal_action}, 2
        );

        spells().add(
            0, "FireBall", 0, std::vector<Action>{damage_player_action}, 4, "int", 1
        );

        races().add(0, "Human", 0);
        races().get(0).setStat("int", +2);
        races().get(0).setStat("cns", -1);

        races().add(1, "Orc", 0);
        races().get(1).setStat("wis", -3);
        races().get(1).setStat("str", +3);

        classes().add(0, "Warrior", 0);
        classes().get(0).addSkill(
            std::make_shared<Skill>(2, "Encourage", 0, std::vector<Action>{buff_action}, 4, 3)
        );

        classes().add(1, "Mage", 0);
        classes().get(1).addSkill(
            std::make_shared<Skill>(3, "Telekinesis", 0, std::vector<Action>{move_action}, 4, 3)
        );
    }

    DemoGameMap::DemoGameMap(GameState& game) : GameMapImpl(game) {
        Character demo_character1(0, "Player1", 0, 12);
        Character demo_character2(0, "Player2", 0, 10);

        locations().add(0, "Start Location", 0, 10, 10);
        locations().add(1, "Second Location", 0, 10, 10);

        createPlayer(std::make_shared<PlayerCharacter>(
            0, std::move(demo_character1), PositionFactory::create(Tile{0, 0}), *this,
            game.classes().safeGet(1), game.races().safeGet(0)
        ));

        createPlayer(std::make_shared<PlayerCharacter>(
            1, std::move(demo_character2), PositionFactory::create(Tile{1, 1}), *this,
            game.classes().safeGet(0), game.races().safeGet(1)
        ));

        locations().get(0).createNPC(2, game.npc().safeGet(0),
                                     PositionFactory::create(Tile{4, 4}),
                                     *this, true);

        locations().get(0).createNPC(3, game.npc().safeGet(0),
                                     PositionFactory::create(Tile{6, 3}),
                                     *this, true);

        players().get(0).consumables().add(Consumable(game.activatableItems().safeGet(0), 2));
    }
}  // namespace DnD
