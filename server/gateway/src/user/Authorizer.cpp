#include <Authorizer.hpp>
#include <UserConnectionImpl.hpp>

#include <ranges>

void UserAuthorizer::authorize_user(ws_connection_t connection, authorize_handler handler) {
    connection->async_read([this, handler, connection](const std::string &message){
        auto view = message
            | std::ranges::views::split(':')
            | std::ranges::views::transform([](auto &&rng) {
                    return std::string(&*rng.begin(), std::ranges::distance(rng));
        });

        auto it = view.begin();

        std::string action = *it++;
        std::string nickname = *it++;
        std::string password = *it;

        if (action == "register") {
            register_user(nickname, password, connection, handler);
        } else if (action == "login") {
            login(nickname, password, connection, handler);
        } else {
            on_authorize_error("Authorization error: unknown action", connection, handler);
        }
    });
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

void UserAuthorizer::on_repeat_login(ws_connection_t connection, authorize_handler handler) {
    on_authorize_error("Authorization error: user with that login already exists", connection, handler);
}

void UserAuthorizer::on_login(std::size_t user_id, ws_connection_t connection, authorize_handler handler) {
    User &user = user_manager.get(user_id);
    auto user_connection = std::make_shared<UserConnectionImpl>(connection, user);
    user.linkConnection(user_connection);

    user_connection->sendMessage("Authorized successfully");

    handler(user_connection);
}

void UserAuthorizer::on_register(User &user, ws_connection_t connection, authorize_handler handler) {
    auto user_connection = std::make_shared<UserConnectionImpl>(connection, user);
    user.linkConnection(user_connection);

    user_connection->sendMessage("Registered successfully");

    handler(user_connection);
}

void InMemoryAuthorizer::login(const std::string &nickname,
                               const std::string &password,
                               ws_connection_t connection,
                               authorize_handler handler) {
    if (user_base.contains(nickname)) {
        auto record = user_base.find(nickname)->second;
        if (record.password == password) {
            on_login(record.id, connection, handler);
        } else {
            on_wrong_credentials(connection, handler);
        }
    } else {
        on_wrong_credentials(connection, handler);
    }
}

void InMemoryAuthorizer::register_user(const std::string &nickname,
                               const std::string &password,
                               ws_connection_t connection,
                               authorize_handler handler) {
    auto &user = user_manager.createUser(nickname);
    user_base.emplace(nickname, UserRecord(user.id(), password));

    on_register(user, connection, handler);
}
