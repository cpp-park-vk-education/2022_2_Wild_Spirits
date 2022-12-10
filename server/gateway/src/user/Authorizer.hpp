#pragma once

#include <functional>
#include <memory>

// #include <Hasher.hpp>
#include <UserConnection.hpp>
#include <UserManager.hpp>

class UserAuthorizer {
private:
    UserManager &user_manager;
    // DBQueue &db;
    using authorize_handler = std::function<void(std::shared_ptr<UserConnection>)>;
    using ws_connection_t = std::shared_ptr<WebSocketConnection>;

    void on_credentials (const std::string &nickname, const std::string &password, ws_connection_t, authorize_handler);
    void on_wrong_credentials_format (ws_connection_t, authorize_handler);

public:
    explicit UserAuthorizer(UserManager &manager): user_manager(manager) {}

    void authorize_user(ws_connection_t, authorize_handler);
};
