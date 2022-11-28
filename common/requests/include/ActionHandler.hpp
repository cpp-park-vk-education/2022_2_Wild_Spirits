#pragma once
#include "client_interfaces.hpp"
#include <deque>
#include "ActionCollector.hpp"




typedef std::deque<Client::Action> action_queue;
typedef std::string string;


class ActionHandler{
private:
    action_queue actions;
    ActionCollector& collector;
public:
    string Action_string(string action_params); 
};
