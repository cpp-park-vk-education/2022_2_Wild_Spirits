#include "ActionHandler.hpp"
#include "Headers.hpp"
#include "Action.hpp"
#include "Actions/Actions.h"
#include "nlohmann/json.hpp"


using nlohmann::json;
string ActionHandler::actionString(LM::Action& action){
    for(std::unique_ptr<TypeHandler>& handler: handlers){
        if(handler -> CanHandle(action)){
            return handler -> Handle(action);
        }
    }
    throw std::runtime_error("Invalid Action");
}

string ActionHandler::actionString(DnD::Action action){

    json action_params;

    return action_params.dump();
}

Client::ActionType ActionHandler::actionHeader(Client::Action action){
    return action.getType();
}

ActionHandler::ActionHandler(): actions(), handlers() {
    handlers.push_back(std::make_unique<MoveHandler>());
    handlers.push_back(std::make_unique<WeaponHandler>());
    handlers.push_back(std::make_unique<SpellHandler>());
    handlers.push_back(std::make_unique<SkillHandler>());
    handlers.push_back(std::make_unique<ConsumableHandler>());
}



