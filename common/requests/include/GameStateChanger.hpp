#pragma once

#include <tuple>
#include <string>
#include "nlohmann/json.hpp"
#include <vector>

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

struct ChangeHandler;

class GameStateChanger{
private:
    DnD::GameState &gamestate;

    std::vector<std::unique_ptr<ChangeHandler>> handlers;

    bool set_field(json changes){

    }
protected:


//    friend ChangeHandler;
public:

    GameStateChanger(DnD::GameState &gamestate);
    bool makechange(std::tuple<std::size_t ,std::string, std::string> setter_params);
    bool makechange(std::tuple<std::string, std::string> setter_params);
    bool makechange(std::string request_part);
    bool makechange(nlohmann::json request_part);
};

struct ChangeHandler{
    virtual bool CanHandle(json changes) = 0;
    virtual void SetField(json changes, DnD::GameState &changing_gamestate) = 0;
    virtual ~ChangeHandler() {
    }
};


//For GameEntityInterface setters
struct ImageHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("image");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct NameHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("name");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct InfoHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("info");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

//For Activatable setters
struct CastTypeHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("cast_type");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct ScalingHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("scaling");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct ActivationCostHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("activation_cost");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
//For Character setters
struct HpMaxHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hp_max");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct ApMaxHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("ap_max");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct BaseArmorHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("base_armor");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct StatsHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("stats");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
//For NPC setters
struct SkillsHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("skills");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
//For CharacterInstance setters
struct ApHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("ap");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct HpHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hp");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct ArmorHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("armor");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

struct PositionHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("position");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
//For NPC_instance setters

struct HostileHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("hostile");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

//For PlayerCharacter setters
struct XPHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("gain_XP");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
//For Skill setters
struct CastCostHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("cast_cost");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};

//For Consumable setters

struct UsesHandler : ChangeHandler{
    bool CanHandle(json changes) override{
        return changes.contains("uses");
    }
    void SetField(json changes, DnD::GameState &changing_gamestate) override{

    }
};
