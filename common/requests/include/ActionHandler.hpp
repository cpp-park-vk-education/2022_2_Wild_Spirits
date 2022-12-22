#pragma once
#include <deque>
#include <string>
#include "ActionCollector.hpp"
#include "nlohmann/json.hpp"
#include "Headers.hpp"
#include "Actions/Action.h"
#include "Actions/MoveAction.h"
#include "Actions/UseActions.h"
#include "Effect.hpp"


typedef std::deque<LM::Action> action_queue;
typedef std::string string;

struct TypeHandler;

class ActionHandler{
private:
    action_queue actions;
    std::vector<std::unique_ptr<TypeHandler>> handlers;
public:
    ActionHandler();
    string actionString(LM::Action& action);

    LM::Action::Type actionHeader(LM::Action &action);

    string actionString(DnD::Action action);

};


struct TypeHandler{
    virtual bool CanHandle(LM::Action& action) = 0;
    virtual std::string Handle(LM::Action& action) = 0;
    virtual ~TypeHandler() {}
};

struct MoveHandler : TypeHandler{
    bool CanHandle(LM::Action& action) override{
        return action.getType() == LM::Action::Type::kMove;
    }

    std::string Handle(LM::Action& action) override{
        nlohmann::json action_view;
        action_view["type"] = "move";
        action_view["X"] = dynamic_cast<LM::MoveAction&>(action).getTargetX();
        action_view["Y"] = dynamic_cast<LM::MoveAction&>(action).getTargetY();
        return action_view.dump();
    }

};

struct WeaponHandler : TypeHandler{
    bool CanHandle(LM::Action& action) override{
        return action.getType() == LM::Action::Type::kUseWeapon;
    }

    std::string Handle(LM::Action& action) override{
        nlohmann::json action_view;
        action_view["type"] = "weapon";
        action_view["id"] = 0; //ВСТАВИТЬ СЮДА get_id, когда появится этот метод в gamestate
        action_view["target_x"] = dynamic_cast<LM::UseAction&>(action).getTargetX();
        action_view["target_y"] = dynamic_cast<LM::UseAction&>(action).getTargetY();
        return action_view.dump();
    }

};

struct ConsumableHandler : TypeHandler{
    bool CanHandle(LM::Action& action) override{
        return action.getType() == LM::Action::Type::kUseConsumable;
    }

    std::string Handle(LM::Action& action) override{
        nlohmann::json action_view;
        action_view["type"] = "consumable";
        action_view["id"] = 0;
        action_view["target_x"] = dynamic_cast<LM::UseAction&>(action).getTargetX();
        action_view["target_y"] = dynamic_cast<LM::UseAction&>(action).getTargetY();
        return action_view.dump();
    }
};

struct SkillHandler : TypeHandler{
    bool CanHandle(LM::Action& action) override{
        return action.getType() == LM::Action::Type::kUseSkill;
    }

    std::string Handle(LM::Action& action) override{
        nlohmann::json action_view;
        action_view["type"] = "skill";
//        action_view["id"] = dynamic_cast<LM::UseAction&>(action).getActivatable().get_id();
        action_view["target_x"] = dynamic_cast<LM::UseAction&>(action).getTargetX();
        action_view["target_y"] = dynamic_cast<LM::UseAction&>(action).getTargetY();
        return action_view.dump();
    }
};

struct SpellHandler : TypeHandler{
    bool CanHandle(LM::Action& action) override{
        return action.getType() == LM::Action::Type::kUseSpell;
    }

    std::string Handle(LM::Action& action) override{
        nlohmann::json action_view;
        action_view["type"] = "spell";
//        action_view["id"] = dynamic_cast<LM::UseAction&>(action).getActivatable().get_id();
        action_view["target_x"] = dynamic_cast<LM::UseAction&>(action).getTargetX();
        action_view["target_y"] = dynamic_cast<LM::UseAction&>(action).getTargetY();
        return action_view.dump();
    }
};