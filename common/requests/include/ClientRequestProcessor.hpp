#pragma once

#include "ClientInterLayer.hpp"
#include "ClientProcessorEngine.hpp"
#include "GameStateChanger.hpp"
#include "TurnOrder.hpp"
#include "sendaccept.hpp"

#include <Classes/Room.h>
#include <ClientConnection.hpp>
#include <EventLoop.hpp>
// TODO: При создании комнаты установить на сервере id клиента как DM
// TODO: Connection должен возвращать id комнаты, как и getROoms

#include <barrier>
#include <thread>

class PlayersID {
private:
    std::unordered_map<std::size_t, std::size_t> client_table;
    std::unordered_map<std::size_t, std::size_t> id_table;

public:
    PlayersID() : client_table(1), id_table(1) {
        client_table.insert(std::make_pair(1, 1)), client_table.insert(std::make_pair(1, 1));
    }
    std::size_t getPlayerId(std::size_t id) { return id_table[id]; }
    std::size_t getClientId(std::size_t player_name) { return client_table[player_name]; }
};

class ClientSideProcessor : public RequestAcceptor, public RequestSender {
public:
    PlayersID playersId;
    std::size_t getPlayerId() { return playersId.getPlayerId(_client_id); }
    std::size_t getClientId() { return _client_id; }
    ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order);
    // ClientSideProcessor(DnD::GameState& gamestate, unsigned int client_id);
    const InterlayerBuffer& getChangesBuffer();
    bool sendRequest(LM::Action& action) override;
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
    // DM Methods
    bool checkUnappliedChanges() const;

    void start();
    void stop();
    void setUpToDate();
private:
    BoostEventLoop loop;
    bool is_connected;
    bool is_authorized;
    void setAuthorized();
    void setConnected();
    void setUnAuthorized();
    void setDisconnected();
    unsigned int _client_id;
    std::size_t _room_id;
    ClientProcessorEngine engine;
    std::shared_ptr<ClientConnection> connection;
    DnD::GameState& gamestate;
    GameStateChanger changer;
    InterlayerBuffer buffer;
    DnD::GameMap& _map;
    DnD::TurnOrder& _order;
    bool SendChangesRequest(LM::Action& action);
    bool ApplyChanges(string changes);
    std::string_view ImageRequest(std::string_view image_hash);
    Header getHeader(std::string request);
    bool ApplicationRequest(queue changes);

    std::jthread loop_thread;
    static inline std::function<void()> on_completion = []() { std::cout << "BC!\n"; };
    std::barrier<decltype(on_completion)> barrier = std::barrier(2, on_completion);
};
