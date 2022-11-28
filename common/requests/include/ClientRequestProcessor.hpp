#pragma once

#include "sendaccept.hpp"
#include "ClientProcessorEngine.hpp"
#include "gateway_interfaces.hpp"
#include "client_interfaces.hpp"
#include "GameStateChanger.hpp"

class ClientSideProcessor: public RequestAcceptor, public RequestSender{
public:
    bool sendRequest(Client::Action action) override;
    bool acceptRequest(std::string request_string) override;
private:
    unsigned int client_id;
    ClientProcessorEngine engine;
    Gateway::ClientConnection* connection;
    Client::GameState& gamestate;
    GameStateChanger GameStateChanger;
    
    bool SendChangesRequest(Client::Action action);
    bool ApplyChanges(queue changes_queue);
    bool ImageRequest(std::string image_hash);
};
