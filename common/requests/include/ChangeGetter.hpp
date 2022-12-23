#pragma once

#include "ChangeCollector.hpp"
#include <deque>
#include <tuple>
#include "nlohmann/json.hpp"
#include "Tile.hpp"

#include <GameState.hpp>

typedef std::deque<std::tuple<string, string>> change_queue;

struct ChangeHandler;

class ChangeGetter{
private:
    std::vector<std::unique_ptr<ChangeHandler>> handlers;
    DnD::LogicProcessor& game_state;
    DnD::GameMap& game_map;
    change_queue changes_queue;


    std::vector<std::string> loading_instances;


    void load_collector(change_queue changes);


public:
    ChangeGetter(DnD::LogicProcessor &gameState, DnD::GameMap &gameMap);
    explicit ChangeGetter(DnD::LogicProcessor &gameState);
    // ChangeGetter(DnD::LogicProcessor &gameState, DnD::GameMap &game_map);
    std::string getChangedFields(nlohmann::json);
    void load_collector(string change);
    std::string getInstance();
};


//Handlers for instance sending
struct InstanceLoader{
    virtual void Load(DnD::GameState& game_state, nlohmann::json& instance_object) = 0;
};


struct NPCLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json npcInstance;
        std::function<void(DnD::NPC)> load_handler = [&npcInstance](DnD::NPC npc_instance){
            nlohmann::json single_instance;
            single_instance["id"] = npc_instance.id();
            single_instance["name"] = npc_instance.name();
            single_instance["image"] = npc_instance.getImageId();
            single_instance["max_hp"] = npc_instance.maxHP();
            single_instance["exp"] = npc_instance.exp();
            single_instance["ap"] = npc_instance.maxActionPoints();
            npcInstance.push_back(single_instance);
        };
        game_state.npc().each(load_handler);
        instance_object["npc"] = npcInstance;
    }
};


struct allCharactersLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json allCharactersInstance;
        std::function<void(DnD::CharacterInstance*)> load_handler = [&allCharactersInstance](DnD::CharacterInstance* character_instance){
            nlohmann::json single_instance;
            single_instance["id"] = character_instance ->id();
            single_instance["name"] = character_instance ->name();
            single_instance["image"] = character_instance ->getImageId();
            single_instance["max_hp"] = character_instance ->maxHP();
            // single_instance["exp"] = character_instance ->exp();
            single_instance["ap"] = character_instance ->maxActionPoints();
            allCharactersInstance.push_back(single_instance);
        };
        game_state.allCharacters().each(load_handler);
        instance_object["allCharacters"] = allCharactersInstance;

    }
};


struct itemsLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json itemsInstance;
        std::function<void(DnD::Item&)> load_handler = [&itemsInstance](DnD::Item& item_instance){
            nlohmann::json single_instance;
            single_instance["id"] = item_instance.id();
            single_instance["name"] = item_instance.name();
            single_instance["image"] = item_instance.getImageId();
            single_instance["cost"] = item_instance.cost();
            itemsInstance.push_back(single_instance);
        };
        game_state.items().each(load_handler);
        instance_object["items"] = itemsInstance;
    }
};


struct activatableItemsLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json activatableItemsInstance;
        std::function<void(DnD::ActivatableItem&)> load_handler = [&activatableItemsInstance](DnD::ActivatableItem& item_instance){
            nlohmann::json single_instance;
            single_instance["id"] = item_instance.id();
            single_instance["name"] = item_instance.name();
            single_instance["image"] = item_instance.getImageId();
            // std::vector<DnD::Action> item_actions = item_instance.actions();
            // for(DnD::Action& action : item_actions){
            //     std::stringstream ss;
            //     ss << action;
            //     single_instance["actions"].push_back(nlohmann::json::parse(ss.str()));
            // }
            single_instance["action_cost"] = item_instance.activateCost();
            single_instance["cost"] = item_instance.cost();
            activatableItemsInstance.push_back(single_instance);
        };
        game_state.activatableItems().each(load_handler);
        instance_object["activatableItems"] = activatableItemsInstance;
    }
};

struct weaponsLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json weaponsInstance;
        std::function<void(DnD::Weapon&)> load_handler = [&weaponsInstance](DnD::Weapon& item_instance){
            nlohmann::json single_instance;
            single_instance["id"] = item_instance.id();
            single_instance["name"] = item_instance.name();
            single_instance["image"] = item_instance.getImageId();
            // std::vector<DnD::Action> item_actions = item_instance.actions();
            // for(DnD::Action& action : item_actions){
            //     single_instance["actions"].push_back(nlohmann::json::parse(ss.str()));
            // }
            single_instance["action_cost"] = item_instance.activateCost();
            single_instance["scaling"] = item_instance.scalesBy();
            weaponsInstance.push_back(single_instance);
        };
        game_state.weapons().each(load_handler);
        instance_object["weapons"] = weaponsInstance;
    }
};


struct spellsLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json spellsInstance;
        std::function<void(DnD::Spell&)> load_handler = [&spellsInstance](DnD::Spell& spell_instance){
            nlohmann::json single_instance;
            single_instance["id"] = spell_instance.id();
            single_instance["name"] = spell_instance.name();
            single_instance["image"] = spell_instance.getImageId();
            // std::vector<DnD::Action> item_actions = spell_instance.actions();
            // for(DnD::Action& action : item_actions){
            //     std::stringstream ss;
            //     ss << action;
            //     single_instance["actions"].push_back(nlohmann::json::parse(ss.str()));
            // }
            single_instance["spell_cost"] = spell_instance.cost();
            single_instance["action_cost"] = spell_instance.activateCost();
            single_instance["scaling"] = spell_instance.scalesBy();
            spellsInstance.push_back(single_instance);
        };
        game_state.spells().each(load_handler);
        instance_object["spells"] = spellsInstance;
    }
};


struct armorLoader : InstanceLoader{
    void Load(DnD::GameState& game_state, nlohmann::json& instance_object) override{
        nlohmann::json armorInstance;
        std::function<void(DnD::Armor&)> load_handler = [&armorInstance](DnD::Armor& armor_instance){
            nlohmann::json single_instance;
            single_instance["id"] = armor_instance.id();
            single_instance["name"] = armor_instance.name();
            single_instance["image"] = armor_instance.getImageId();
            single_instance["defense"] = armor_instance.defense();
            single_instance["cost"] = armor_instance.cost();
            armorInstance.push_back(single_instance);
        };
        game_state.armor().each(load_handler);
        instance_object["armor"] = armorInstance;
    }
};




//Handlers for change
struct ChangeHandler{
    virtual ~ChangeHandler();
    virtual bool CanHandle(nlohmann::json request) = 0;
    virtual std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) = 0;

};


struct MoveHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "move";
    }

    std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) override{
        std::stringstream ss;
        request["X"];
        request["Y"];

        return ss.str();
    }

};

struct WeaponHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "weapon";
    }

    std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) override{
        std::stringstream ss;
//        DnD::Tile target_tile(request["target_x"], request["target_y"]);
        ss << std::get<0>(logic_processor.useActivatable(request["player_id"], std::string(request["type"]), request["id"], std::vector<DnD::Tile>()));
        return ss.str();
    }

};

struct ConsumableHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "consumable";
    }

    std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) override{
        std::stringstream ss;
        DnD::Tile target_tile{request["target_x"], request["target_y"]};
        ss << std::get<0>(logic_processor.useActivatable(request["player_id"], std::string(request["type"]), request["id"], std::vector<DnD::Tile>()));
        return ss.str();
    }
};

struct SkillHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "skill";
    }

    std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) override{
        std::stringstream ss;
        DnD::Tile target_tile{request["target_x"], request["target_y"]};
        ss << std::get<0>(logic_processor.useActivatable(request["player_id"], std::string(request["type"]), request["id"], std::vector<DnD::Tile>()));
        return ss.str();
    }
};

struct SpellHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "spell";
    }

    std::string Handle(nlohmann::json request, DnD::LogicProcessor& logic_processor) override{
        std::stringstream ss;
        request["id"];
        request["target_x"];
        request["target_y"];
        return ss.str();
    }
};



