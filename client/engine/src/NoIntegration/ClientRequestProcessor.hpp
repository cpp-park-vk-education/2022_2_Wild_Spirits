#pragma once

#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "GameMap.hpp"
#include "GameState.hpp"
#include "TurnOrder.hpp"
#include <Actions/Action.h>
#include <Classes/Room.h>

class InterlayerBuffer {
public:
    InterlayerBuffer(const std::initializer_list<std::pair<std::string, long long>> data = {})
        : m_ApplyFlag(false) {
        m_ChangesBuffer.insert(m_ChangesBuffer.end(), data.begin(), data.end());
        if (data.size()) {
            m_ApplyFlag = true;
        }
    }

    void addChange(const std::string& name, long long change) {
        m_ChangesBuffer.emplace_back(name, change);
        m_ApplyFlag = true;
    }

    void clear() { m_ChangesBuffer.clear(); }

    std::pair<std::string, long long> getNextChange() {
        std::pair<std::string, long long> change;
        change = m_ChangesBuffer.front();
        m_ChangesBuffer.pop_front();
        if (m_ChangesBuffer.empty()) {
            m_ApplyFlag = false;
        }
        return change;
    }

    bool hasUnseenChanges() const { return m_ApplyFlag; }

protected:
    std::deque<std::pair<std::string, long long>> m_ChangesBuffer;
    bool m_ApplyFlag;
};

class ClientSideProcessor {
public:
    ClientSideProcessor(DnD::GameState& gamestate, DnD::GameMap& map, DnD::TurnOrder& order);

    std::size_t getPlayerId() const { return m_PlayerId; }
    std::size_t getClientId() const { return _client_id; }

    InterlayerBuffer& getChangesBuffer() { return m_ChangesBuffer; }
    bool sendRequest(LM::Action& action);
    std::string sendRequest(const std::string& request);
    bool getImage(size_t hash, std::shared_ptr<std::string>) const;
    bool acceptRequest(const std::string& request_string) const;
    bool Connection(const std::string& ip, const std::string& port);
    LM::Room CreateRoom() const;
    bool StartGame() const;
    bool ConnectToRoom(LM::Room room) const;
    std::vector<LM::Room> GetRooms() const;
    bool Register(const std::string& login, const std::string& password);
    bool Login(const std::string& login, const std::string& password);
    bool isAuthorized() const;
    bool checkUnappliedChanges() const;

    bool setUpToDate();
    bool setUnappliedChanges(bool newVal);
    bool applyChanges(const std::vector<std::pair<std::string, int64_t>>& changes);
    std::pair<bool, size_t> sendImage(const std::string& source) const;

    void localApplyChanges(const std::vector<std::pair<std::string, int64_t>>& changes);

private:
    bool is_connected;
    bool is_authorized;
    bool is_changed;
    uint32_t _client_id;
    DnD::GameState& _gamestate;
    DnD::GameMap& m_Map;
    DnD::TurnOrder& _order;

    size_t m_PlayerId = 0;
    InterlayerBuffer m_ChangesBuffer;
};