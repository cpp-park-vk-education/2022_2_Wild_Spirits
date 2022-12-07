#pragma once


#include <unordered_map>
#include "string"
#include "RequestStringGenerator.hpp"


class ActionCollector{
public:
    ActionCollector(RequestStringGenerator &generator);
    void add_action(std::string description, std::string params);
    std::unordered_map<std::string, std::string> flush();

private:
    std::unordered_map<std::string, std::string> current_actions;
    RequestStringGenerator& generator;
};

