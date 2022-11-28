#pragma once

#include "RequestStringGenerator.hpp"
#include "StringRequestParser.hpp"
#include "ActionHandler.hpp"
#include "ActionCollector.hpp"
#include <deque>
#include <memory>
#include <unordered_map>
#include <tuple>

typedef std::deque<std::tuple<std::string, std::string>> setter_queue;
typedef std::string string;

class ClientProcessorEngine{
private:
    std::shared_ptr<RequestStringGenerator> generator;
    std::shared_ptr<RequestStringParser> parser;
    std::shared_ptr<ActionCollector> collector;
public:
    std::shared_ptr<ActionHandler> handler;
    setter_queue getSetterQueue(string);
    string getRequestString(std::unordered_map<std::string, string>);
    
};
