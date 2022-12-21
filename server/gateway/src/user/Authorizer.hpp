#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

// #include <Hasher.hpp>
#include <UserConnection.hpp>
#include <UserManager.hpp>

class UserAuthorizer {
protected:
    UserManager &user_manager;
    // DBQueue &db;
    using authorize_handler = std::function<void(std::shared_ptr<UserConnection>)>;
    using ws_connection_t = std::shared_ptr<WebSocketConnection>;

    void on_authorize_error(const std::string&, ws_connection_t, authorize_handler);
    void on_wrong_credentials_format (ws_connection_t, authorize_handler);
    void on_wrong_credentials(ws_connection_t, authorize_handler);

    virtual void login(const std::string &nickname, const std::string &password, ws_connection_t, authorize_handler) = 0;
    void on_login(std::size_t user_id, ws_connection_t, authorize_handler);
    void on_register(User &user, ws_connection_t, authorize_handler);

public:
    explicit UserAuthorizer(UserManager &manager): user_manager(manager) {}

    virtual void authorize_user(ws_connection_t, authorize_handler);
};

struct UserRecord {
    std::size_t id;
    std::string password;

    UserRecord(std::size_t id, const std::string &password): id(id), password(password) {}
};


class InMemoryAuthorizer: public UserAuthorizer {
private:
    std::unordered_map<std::string, UserRecord> user_base;

public:
    explicit InMemoryAuthorizer(UserManager &manager): UserAuthorizer(manager) {}

    virtual void login(const std::string &nickname, 
                       const std::string &password,
                       ws_connection_t,
                       authorize_handler) override;

    void registerUser(const std::string &nickname,
                  const std::string &password,
                  ws_connection_t,
                  authorize_handler);
};
