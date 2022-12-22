#include <Authorizer.hpp>
#include <UserConnectionImpl.hpp>

void UserAuthorizer::authorize_user(ws_connection_t connection, authorize_handler handler) {
    // connection->async_read([this, handler, connection](std::string message){
    //     std::size_t delimiter_pos = message.find(':');

    //     if (delimiter_pos == std::string::npos) {
    //         on_wrong_credentials_format(connection, handler);
    //         return;
    //     }

    //     std::string nickname = message.substr(0, delimiter_pos);
    //     std::string password = message.substr(delimiter_pos);
    //     login(nickname, password, connection, handler);
    // });
    // registerUser("nickname", "password", connection, handler);

    login("nickname", "password", connection, handler);
}

void UserAuthorizer::on_authorize_error(const std::string &error_message,
                                        ws_connection_t connection,
                                        authorize_handler handler) {
    connection->async_write(error_message,
    [this, connection, handler](bool status){
        authorize_user(connection, handler);
    });
}

void UserAuthorizer::on_wrong_credentials_format(ws_connection_t connection, authorize_handler handler) {
    on_authorize_error("Authorization error: wrong format", connection, handler);
}

void UserAuthorizer::on_wrong_credentials(ws_connection_t connection, authorize_handler handler) {
    on_authorize_error("Authorization error: wrong login or password", connection, handler);
}

void UserAuthorizer::on_login(std::size_t user_id, ws_connection_t connection, authorize_handler handler) {
    User &user = user_manager.get(user_id);
    auto user_connection = std::make_shared<UserConnectionImpl>(connection, user);
    user.linkConnection(user_connection);

    user_connection->sendMessage("Authorized succesfully");

    handler(user_connection);
}

void UserAuthorizer::on_register(User &user, ws_connection_t connection, authorize_handler handler) {
    auto user_connection = std::make_shared<UserConnectionImpl>(connection, user);
    user.linkConnection(user_connection);

    // user_connection->sendMessage("Registered succesfully");

    handler(user_connection);
}

void InMemoryAuthorizer::login(const std::string &nickname,
                               const std::string &password,
                               ws_connection_t connection,
                               authorize_handler handler) {
    // if (user_base.contains(nickname)) {
    //     auto record = user_base.find(nickname)->second;
    //     if (record.password == password) {
    //         on_login(record.id, connection, handler);
    //     } else {
    //         on_wrong_credentials(connection, handler);
    //     }
    // } else {
    //     registerUser(nickname, password, connection, handler);
    // }
    registerUser(nickname, password, connection, handler);
}

void InMemoryAuthorizer::registerUser(const std::string &nickname,
                               const std::string &password,
                               ws_connection_t connection,
                               authorize_handler handler) {
    auto &user = user_manager.createUser(nickname);
    user_base.emplace(nickname, UserRecord(user.id(), password));

    on_register(user, connection, handler);
}
