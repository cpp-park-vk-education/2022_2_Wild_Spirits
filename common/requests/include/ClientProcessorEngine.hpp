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

class PlayerCharacters{
private:
    std::unordered_map<unsigned int, std::string> player_table;
    std::unordered_map<std::string, std::size_t> id_table;
public:
    PlayerCharacters();
    std::string getPlayerName(unsigned int id);
    unsigned int getUserId(std::string player_name);

};

class ClientProcessorEngine{
public:
    std::shared_ptr<RequestStringGenerator> generator;
    std::shared_ptr<ClientRequestStringParser> parser;

public:
    std::deque<nlohmann::json> getAnotherSetterQueue(string request_string);
    ClientProcessorEngine();
    std::shared_ptr<ActionHandler> handler;
    setter_queue getSetterQueue(string request);
    string getRequestString(std::string action_string, LM::Action::Type header);

    string getRequestString(std::string request_string, Header header);
    bool hasChanges() const;
};
