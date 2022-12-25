#pragma once

#include <memory>
#include <string>
#include <vector>

#include "GameMap.hpp"
#include "GameState.hpp"
#include "TurnOrder.hpp"
#include <Actions/Action.h>
#include <Classes/Room.h>

class ClientSideProcessor {
public:
    ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order);

    std::size_t getPlayerId() { return 0; }
    std::size_t getClientId() { return _client_id; }

    bool sendRequest(LM::Action& action);
    std::string sendRequest(std::string request);
    bool getImage(size_t hash, std::shared_ptr<std::string>);
    bool acceptRequest(std::string request_string);
    bool Connection(std::string ip, std::string port);
    LM::Room CreateRoom();
    bool StartGame();
    bool ConnectToRoom(LM::Room room);
    std::vector<LM::Room> GetRooms();
    bool Register(std::string login, std::string password);
    bool Login(std::string, std::string password);
    bool isAuthorized() const;
    bool checkUnappliedChanges() const;

    bool setUpToDate();
    bool setUnappliedChanges(bool newVal);

private:
    bool is_connected;
    bool is_authorized;
    bool is_changed;
    uint32_t _client_id;
    DnD::GameState& _gamestate;
    DnD::GameMap& _map;
    DnD::TurnOrder& _order;
};