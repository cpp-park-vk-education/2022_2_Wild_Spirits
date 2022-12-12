#include "ActionHandler.hpp"
#include "Headers.hpp"
#include "Action.hpp"
#include "nlohmann/json.hpp"


using nlohmann::json;
string ActionHandler::actionString(Client::Action action){
    std::string action_view;
    json action_params;

    action_params["type"] = action.getType();
    return action_params.dump();
}

string ActionHandler::actionString(DnD::Action action){

    json action_params;
    return action_params.dump();
}

Client::ActionType ActionHandler::actionHeader(Client::Action action){
    return action.getType();
}

ActionHandler::ActionHandler(): actions() {

}
