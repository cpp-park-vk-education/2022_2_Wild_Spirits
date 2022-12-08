#include "ActionCollector.hpp"
#include "string"

void ActionCollector::add_action(std::string description, std::string params){

}

std::unordered_map<std::string, std::string> ActionCollector::flush(){


    return current_actions;
}

ActionCollector::ActionCollector(RequestStringGenerator &generator) : generator(generator) {

}
