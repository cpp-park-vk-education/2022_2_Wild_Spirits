#pragma once

#include "sendaccept.hpp"
#include "ClientProcessorEngine.hpp"
#include "gateway_interfaces.hpp"
#include "client_interfaces.hpp"
#include "GameStateChanger.hpp"

class ClientSideProcessor: public RequestAcceptor, public RequestSender{
private:
    unsigned int client_id;
    ClientProcessorEngine engine;
    Gateway::ClientConnection* connection;
    Client::GameState& gamestate;
    GameStateChanger GameStateChanger;
    
    bool SendChangesRequest(Client::Action);
    bool ApplyChanges(queue);
    bool ImageRequest(std::string);
};
