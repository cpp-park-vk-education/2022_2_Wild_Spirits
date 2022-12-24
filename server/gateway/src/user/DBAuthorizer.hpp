#pragma once

#include <Authorizer.hpp>
#include <DBQueue.hpp>

class DBAuthorizer: public UserAuthorizer {
private:
    DBQueue &db;

public:
    DBAuthorizer(UserManager &manager, DBQueue &db);

    virtual void login(const std::string &nickname, 
                       const std::string &password,
                       ws_connection_t,
                       authorize_handler) override;

    virtual void register_user(const std::string &nickname,
                  const std::string &password,
                  ws_connection_t,
                  authorize_handler) override;
};
