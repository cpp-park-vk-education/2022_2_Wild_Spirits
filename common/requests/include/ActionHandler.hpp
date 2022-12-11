#pragma once
#include "client_interfaces.hpp"
#include <deque>
#include <string>
#include "ActionCollector.hpp"
#include "nlohmann/json.hpp"
#include "Headers.hpp"


typedef std::deque<Client::Action> action_queue;
typedef std::string string;


class ActionHandler{
private:
    action_queue actions;
public:
    ActionHandler();
    string actionString(Client::Action action);

    Client::ActionType actionHeader(Client::Action action);
};
