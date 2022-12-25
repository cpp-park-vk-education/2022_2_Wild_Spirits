#include "ClientRequestProcessor.hpp"

ClientSideProcessor::ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order)
    : is_connected(false),
      is_authorized(false),
      is_changed(false),
      _client_id(0),
      _gamestate(gamestate),
      _map(map),
      _order(order) { }

bool ClientSideProcessor::sendRequest(LM::Action& action) {
    // TODO Add action logic
    is_changed = true;
    return true;
}

std::string ClientSideProcessor::sendRequest(std::string request) {
    // Is something where ???
    return "";
}

bool ClientSideProcessor::getImage(size_t hash, std::shared_ptr<std::string> data) {
    *data = DnD::TestImages::getSourceById(hash);

    return true;
}

bool ClientSideProcessor::acceptRequest(std::string request_string) { return true; }

bool ClientSideProcessor::Connection(std::string ip, std::string port) {
    is_connected = true;
    return is_connected;
}

LM::Room ClientSideProcessor::CreateRoom() { return LM::Room(LM::RoomProps { 0 }); }

bool ClientSideProcessor::StartGame() {
    // TODO add some logic
    return true;
}

bool ClientSideProcessor::ConnectToRoom(LM::Room room) { return true; }

std::vector<LM::Room> ClientSideProcessor::GetRooms() {
    return std::vector({ LM::Room(LM::RoomProps { 0 }), LM::Room(LM::RoomProps { 1 }),
                         LM::Room(LM::RoomProps { 2 }), LM::Room(LM::RoomProps { 3 }) });
}

bool ClientSideProcessor::Register(std::string login, std::string password) { return true; }

bool ClientSideProcessor::Login(std::string, std::string password) {
    is_authorized = true;

    return is_authorized;
}

bool ClientSideProcessor::isAuthorized() const { return is_authorized; }

bool ClientSideProcessor::checkUnappliedChanges() const { return is_changed; }

bool ClientSideProcessor::setUnappliedChanges(bool newVal) {
    is_changed = newVal;
    return is_changed;
}
