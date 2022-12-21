#pragma once

#include <unordered_map>
#include <string>

typedef std::string string;

class ChangeCollector{
private:
    std::unordered_map<std::string, std::string> changed_fields;
public:
    ChangeCollector();
    void add_change(string description, string new_value);
    std::unordered_map<string, string> flush();
};

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