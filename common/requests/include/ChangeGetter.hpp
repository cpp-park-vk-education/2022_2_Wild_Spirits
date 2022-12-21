#pragma once

#include "room_interfaces.hpp"
#include "ChangeCollector.hpp"
#include <deque>
#include <tuple>
#include "nlohmann/json.hpp"
#include "Tile.hpp"


typedef std::deque<std::tuple<string, string>> change_queue;


class ChangeGetter{
private:
    Room::GameLogicProcessor& game_state;
    ChangeCollector& collector;
    change_queue changes_queue;
    void load_collector(change_queue changes);

public:
    ChangeGetter(ChangeCollector &collector, Room::GameLogicProcessor &gameState);
    nlohmann::json getChangedFields(nlohmann::json);
    void load_collector(string change);
};


struct ChangeHandler{
    virtual ~ChangeHandler();
    virtual bool CanHandle(nlohmann::json request) = 0;
    virtual std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) = 0;

};


struct MoveHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "move";
    }

    std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) override{
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

    std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) override{
        std::stringstream ss;
        DnD::Tile target_tile(request["target_x"], request["target_y"]);
        ss << logic_processor.useActivatable(request["player_id"], request["type"], request["id"], std::vector<DnD::Tile>());
        return ss.str();
    }

};

struct ConsumableHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "consumable";
    }

    std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) override{
        std::stringstream ss;
        DnD::Tile target_tile(request["target_x"], request["target_y"]);
        ss << logic_processor.useActivatable(request["player_id"], request["type"], request["id"], std::vector<DnD::Tile>());
        return ss.str();
    }
};

struct SkillHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "skill";
    }

    std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) override{
        std::stringstream ss;
        DnD::Tile target_tile(request["target_x"], request["target_y"]);
        ss << logic_processor.useActivatable(request["player_id"], request["type"], request["id"], std::vector<DnD::Tile>());
        return ss.str();
    }
};

struct SpellHandler : ChangeHandler{
    bool CanHandle(nlohmann::json request) override{
        return request["type"] == "spell";
    }

    std::string Handle(nlohmann::json request, Room::GameLogicProcessor& logic_processor) override{
        std::stringstream ss;
        request["id"];
        request["target_x"];
        request["target_y"];
        return ss.str();
    }
};