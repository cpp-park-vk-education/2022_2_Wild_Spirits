#pragma once
#include "client_interfaces.hpp"
#include <deque>
#include <string>
#include "ActionCollector.hpp"
#include "nlohmann/json.hpp"


typedef std::deque<Client::Action> action_queue;
typedef std::string string;


class ActionHandler{
private:
    action_queue actions;
    ActionCollector& collector;
public:
    ActionHandler(ActionCollector &collector);
    string Action_string(string action_params); 
};
