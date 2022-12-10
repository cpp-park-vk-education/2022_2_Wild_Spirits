#include <Authorizer.hpp>
#include <UserConnectionImpl.hpp>

void UserAuthorizer::authorize_user(ws_connection_t connection, authorize_handler handler) {
    connection->async_read([this, handler, connection](std::string message){
        std::size_t delimiter_pos = message.find(':');

        if (delimiter_pos == std::string::npos) {
            on_wrong_credentials_format(connection, handler);
            return;
        }

        std::string nickname = message.substr(0, delimiter_pos);
        std::string password = message.substr(delimiter_pos);

        on_credentials(nickname, password, connection, handler);
    });
}

void UserAuthorizer::on_wrong_credentials_format(ws_connection_t connection, authorize_handler handler) {
    connection->async_write("Authorization error: wrong format",
        [this, connection, handler](){
            authorize_user(connection, handler);
        });
}

void UserAuthorizer::on_credentials(const std::string &nickname,
                                    const std::string &password,
                                    ws_connection_t connection,
                                    authorize_handler handler) {
    User &user = user_manager.createUser(nickname);
    auto user_connection = std::make_shared<UserConnectionImpl>(connection, user);
    user.linkConnection(user_connection);

    user_connection->sendMessage("Authorized succesfully");

    handler(user_connection);
}
