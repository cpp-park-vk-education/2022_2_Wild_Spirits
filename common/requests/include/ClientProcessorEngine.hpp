#pragma once

#include "RequestStringGenerator.hpp"
#include "StringRequestParser.hpp"
#include "ActionHandler.hpp"
#include "ActionCollector.hpp"
#include "Headers.hpp"
#include <deque>
#include <memory>
#include <unordered_map>
#include <tuple>

typedef std::deque<std::tuple<std::string, std::string>> setter_queue;
typedef std::string string;

class ClientProcessorEngine{
private:
    std::shared_ptr<RequestStringGenerator> generator;
    std::shared_ptr<ClientRequestStringParser> parser;

public:
    ClientProcessorEngine();
    std::shared_ptr<ActionHandler> handler;
    setter_queue getSetterQueue(string request);
    string getRequestString(std::string action_string, Client::ActionType header);
    string getRequestString(std::string request_string, Header header);
    bool hasChanges() const;
};
