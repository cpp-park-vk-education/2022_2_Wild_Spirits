#pragma once

#include "client_interfaces.hpp"
#include <tuple>
#include <string>
#include "nlohmann/json.hpp"

#include "GameState.hpp"
#include "Activatable.hpp"
#include "GameEntity.hpp"
#include "Character.hpp"
#include "CharacterInstance.hpp"
#include "NPC_Instance.hpp"
#include "PlayerCharacter.hpp"


using nlohmann::json;
//new entities creation
//GameEntity interface (name, image , info)
//Activatable (cast_type, scaling, activation cost)
//Character (hp_max, max_actionPoints, base_armor_class, stats)
//NPC (skills)
//CharacterInstance(actionPoints, hp, armor_class, Position)
//NPC_instance (turnHostile, turnFriendly)
//PlayerCharacter(gainXP)
//Skill (castCost)
//Consumable (uses)
class GameStateChanger{
private:
    DnD::GameState &gamestate;
    template <typename T>
    bool set_field(json changes){
        bool state = true;
        if (std::is_same_v<T, DnD::GameEntityInterface>() && changes.contains("name")\
        && changes.contains("image")\
        && changes.contains("info")){

        }
        else if (std::is_same_v<T, DnD::Activatable>() && changes.contains("cast_type")\
        && changes.contains("scaling")\
        && changes.contains("activation_cost")){

        }
        else if (std::is_same_v<T, DnD::Character>() && changes.contains("hp_max")\
        && changes.contains("max_action_points")\
        && changes.contains("base_armor_class")){

        }
        else if (std::is_same_v<T, DnD::CharacterInstance>() && changes.contains("action_points")\
        && changes.contains("hp")\
        && changes.contains("armor_class")\
        && changes.contains("position")){

        }
        else if (std::is_same_v<T, DnD::NPC_Instance>() && changes.contains("hostile")){

        }
        else if (std::is_same_v<T, DnD::PlayerCharacter>() && changes.contains("XP")){

        }
        else if (std::is_same_v<T, DnD::Consumable>() && changes.contains("uses")){

        }
        else{
            return state;
        }
    }
public:
    GameStateChanger(DnD::GameState &gamestate);
    bool makechange(std::tuple<std::size_t ,std::string, std::string> setter_params);
    bool makechange(std::tuple<std::string, std::string> setter_params);
};

//std::unordered_map<std::string, > storage_table {
//
//};
//
//std::unordered_map<std::string, std::function<void(std::size_t, std::string)>> setters_table{
//        {""}
//};


