#pragma once


#include "sendaccept.hpp"
#include "ClientProcessorEngine.hpp"
#include "GameStateChanger.hpp"
#include "ClientInterLayer.hpp"
#include "TurnOrder.hpp"
//TODO: При создании комнаты установить на сервере id клиента как DM
//TODO: Connection должен возвращать id комнаты, как и getROoms

class PlayerCharacters{
private:
    std::unordered_map<unsigned int, std::string> player_table;
    std::unordered_map<std::string, std::size_t> id_table;
public:
    PlayerCharacters();
    std::string getPlayerName(unsigned int id);
    unsigned int getUserId(std::string player_name);

};


class ClientSideProcessor: public RequestAcceptor, public RequestSender{
public:
    ClientSideProcessor(DnD::GameState &gamestate, DnD::GameMap& map, DnD::TurnOrder& order);
    ClientSideProcessor(DnD::GameState &gamestate, unsigned int client_id);

    bool sendRequest(LM::Action action) override;
    bool sendRequest(LM::Action action);
    std::string sendRequest(std::string request);
    bool getImage(std::string_view hash, std::shared_ptr<std::string>);
    bool acceptRequest(string request_string) override;
    bool Connection(std::string ip, std::string port);
    LM::Room CreateRoom();
    bool StartGame();
    bool ConnectToRoom(LM::Room room);
    std::vector<LM::Room> GetRooms();
    bool Register(std::string login, std::string password);
    bool Login(std::string, std::string password);
    bool isAuthorized() const;
    //DM Methods
    bool checkUnappliedChanges() const;
private:
    BoostEventLoop loop;
    bool is_connected;
    bool is_authorized;
    unsigned int _client_id;
    ClientProcessorEngine engine;
    std::shared_ptr<ClientConnection> connection;
    DnD::GameState& gamestate;
    GameStateChanger changer;
    InterlayerBuffer buffer;
    DnD::GameMap& _map;
    DnD::TurnOrder& _order;
    bool SendChangesRequest(LM::Action action);
    bool ApplyChanges(string changes);
    std::string_view ImageRequest(std::string_view image_hash);
    Header getHeader(std::string request);
    bool ApplicationRequest(queue changes);
};
