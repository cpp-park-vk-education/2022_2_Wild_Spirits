#include "ClientRequestProcessor.hpp"

#include <iostream>

#include <Actions/MoveAction.h>

ClientSideProcessor::ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order)
    : is_connected(false),
      is_authorized(false),
      is_changed(false),
      _client_id(0),
      _gamestate(gamestate),
      m_Map(map),
      _order(order) { }

const char ACTION_MOVE_X[] = "MoveX";
const char ACTION_MOVE_Y[] = "MoveY";
const char ACTION_USE_X[] = "UseX";
const char ACTION_USE_Y[] = "UseY";
const char ACTION_USE_DMG[] = "Dmg";

bool ClientSideProcessor::sendRequest(LM::Action& action) {
    switch (action.getType()) {
        case LM::Action::Type::kMove: {
            std::cout << "Action kMove\n";
            m_ChangesBuffer.addChange(ACTION_MOVE_X, dynamic_cast<LM::MoveAction&>(action).getTargetX());
            m_ChangesBuffer.addChange(ACTION_MOVE_Y, dynamic_cast<LM::MoveAction&>(action).getTargetY());
            break;
        }
        case LM::Action::Type::kUseWeapon:
        case LM::Action::Type::kUseSpell:
        case LM::Action::Type::kUseSkill:
        case LM::Action::Type::kUseConsumable: {
            std::cout << "Action kUse\n";
            m_ChangesBuffer.addChange(ACTION_USE_X, dynamic_cast<LM::UseAction&>(action).getTargetX());
            m_ChangesBuffer.addChange(ACTION_USE_Y, dynamic_cast<LM::UseAction&>(action).getTargetY());
            m_ChangesBuffer.addChange(ACTION_USE_DMG, 2);
            break;
        }
        default: break;
    }

    is_changed = true;
    return true;
}

std::string ClientSideProcessor::sendRequest(const std::string& request) {
    return std::to_string(m_PlayerId);
}

bool ClientSideProcessor::getImage(size_t hash, std::shared_ptr<std::string> data) const {
    (void)is_connected;
    *data = DnD::TestImages::getSourceById(hash);

    return true;
}

bool ClientSideProcessor::acceptRequest(const std::string& request_string) const {
    (void)is_connected;

    return true;
}

bool ClientSideProcessor::Connection(const std::string& ip, const std::string& port) {
    is_connected = true;
    return is_connected;
}

LM::Room ClientSideProcessor::CreateRoom() const {
    (void)is_connected;
    return LM::Room(LM::RoomProps { 0 });
}

bool ClientSideProcessor::StartGame() const {
    (void)is_connected;

    return true;
}

bool ClientSideProcessor::ConnectToRoom(LM::Room room) const {
    (void)is_connected;

    return true;
}

std::vector<LM::Room> ClientSideProcessor::GetRooms() const {
    (void)is_connected;

    return std::vector({ LM::Room(LM::RoomProps { 0 }), LM::Room(LM::RoomProps { 1 }),
                         LM::Room(LM::RoomProps { 2 }), LM::Room(LM::RoomProps { 3 }) });
}

bool ClientSideProcessor::Register(const std::string& login, const std::string& password) {
    is_authorized = true;

    return is_authorized;
}

bool ClientSideProcessor::Login(const std::string&, const std::string& password) {
    is_authorized = true;

    return is_authorized;
}

bool ClientSideProcessor::isAuthorized() const { return is_authorized; }

bool ClientSideProcessor::checkUnappliedChanges() const { return is_changed; }

bool ClientSideProcessor::setUpToDate() {
    is_changed = false;

    return is_changed;
}

bool ClientSideProcessor::setUnappliedChanges(bool newVal) {
    is_changed = newVal;

    return is_changed;
}

bool ClientSideProcessor::applyChanges(const std::vector<std::pair<std::string, int64_t>>& changes) {
    localApplyChanges(changes);

    is_changed = true;

    return true;
}

std::pair<bool, size_t> ClientSideProcessor::sendImage(const std::string& source) const {
    (void)is_connected;

    size_t id = DnD::TestImages::addImage(source);
    return std::make_pair(true, id);
}

#define CRP_ACTION_MACRO_EXPR(actionName, expr)                                                              \
    if (name == actionName) {                                                                                \
        expr(value);                                                                                         \
        continue;                                                                                            \
    }

#define CRP_ACTION_MACRO_ASAN(actionName, asan)                                                              \
    if (name == actionName) {                                                                                \
        asan = value;                                                                                        \
        continue;                                                                                            \
    }

void ClientSideProcessor::localApplyChanges(const std::vector<std::pair<std::string, int64_t>>& changes) {
    int64_t useX = -1;
    int64_t useY = -1;
    int64_t useDMG = -1;
    for (const auto& change : changes) {
        auto name = change.first;
        auto value = change.second;
        auto player = m_Map.players().safeGet(0);
        CRP_ACTION_MACRO_EXPR(ACTION_MOVE_X, player->setPosX);
        CRP_ACTION_MACRO_EXPR(ACTION_MOVE_Y, player->setPosY);
        CRP_ACTION_MACRO_ASAN(ACTION_USE_X, useX);
        CRP_ACTION_MACRO_ASAN(ACTION_USE_Y, useY);
        CRP_ACTION_MACRO_ASAN(ACTION_USE_DMG, useDMG);
    }
    std::cout << useX << " " << useY << " " << useDMG << std::endl;
    if (useX != -1 && useY != -1 && useDMG != -1) {
        for (auto [id, player] : m_Map.players()) {
            if (player->centerPos().x == useX && player->centerPos().y == useY) {
                player->takeDamage(useDMG);
            }
        }

        for (auto [id, npc] : m_Map.currentLocation().npc()) {
            if (npc->centerPos().x == useX && npc->centerPos().y == useY) {
                npc->takeDamage(useDMG);
            }
        }
    }
}
