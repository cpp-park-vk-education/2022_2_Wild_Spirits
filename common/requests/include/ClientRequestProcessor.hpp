#pragma once

#include "sendaccept.hpp"
#include "ClientProcessorEngine.hpp"
#include "gateway_interfaces.hpp"
#include "client_interfaces.hpp"
#include "GameStateChanger.hpp"

class ClientSideProcessor: public RequestAcceptor, public RequestSender{
public:
    ClientSideProcessor(Client::GameState &gamestate, unsigned int client_id);//Передать в конструктор ip, port
    bool sendRequest(Client::Action action) override;
    bool sendRequest(Client::Request request) override;
    bool getImage(std::string_view hash, std::shared_ptr<std::string>);
    bool acceptRequest(std::string_view request_string) override;

private:
    unsigned int _client_id;
    ClientProcessorEngine engine;
    std::shared_ptr<Gateway::ClientConnection> connection;
    Client::GameState& gamestate;
    GameStateChanger changer;
    
    bool SendChangesRequest(Client::Action action);
    bool ApplyChanges(queue changes_queue);
    std::string_view ImageRequest(std::string_view image_hash);
};
