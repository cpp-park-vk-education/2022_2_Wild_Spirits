#pragma once

#include "sendaccept.hpp"
#include "ClientProcessorEngine.hpp"
#include "gateway_interfaces.hpp"
#include "client_interfaces.hpp"
#include "GameStateChanger.hpp"
#include "ClientInterLayer.hpp"
//TODO: При создании комнаты установить на сервере id клиента как DM
//TODO: Connection должен возвращать id комнаты, как и getROoms

class ClientSideProcessor: public RequestAcceptor, public RequestSender{
public:
    ClientSideProcessor(Client::GameState &gamestate);//Передать в конструктор ip, port
    bool sendRequest(Client::Action action) override;
    bool sendRequest(Client::Request request) override;
    bool getImage(std::string_view hash, std::shared_ptr<std::string>);
    bool acceptRequest(string request_string) override;
    bool Connection(std::string ip, std::string port);
    std::size_t CreateRoom();
    bool StartGame();
    bool ConnectToRoom();
    //DM Methods
    bool checkUnappliedChanges() const;
private:
    bool is_connected;
    unsigned int _client_id;
    ClientProcessorEngine engine;
    std::shared_ptr<Gateway::ClientConnection> connection;
    Client::GameState& gamestate;
    GameStateChanger changer;
    InterlayerBuffer buffer;

    bool SendChangesRequest(Client::Action action);
    bool ApplyChanges(string changes);
    std::string_view ImageRequest(std::string_view image_hash);
    Header getHeader(std::string request);
    bool ApplicationRequest(queue changes);
};
