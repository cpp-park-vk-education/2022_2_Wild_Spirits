#include <DBAuthorizer.hpp>

#include <crypto.hpp>

DBAuthorizer::DBAuthorizer(UserManager &manager, DBQueue &db): 
    UserAuthorizer(manager), db(db) {}

void DBAuthorizer::login(const std::string &nickname,
                         const std::string &password,
                         ws_connection_t connection,
                         authorize_handler handler) {
    db.execute_query([=, this](pqxx::work &tr){
        auto user = UsersTable::optional_find_by(tr, "nickname", nickname);
        if (user.has_value()) {
            std::string password_hash = Crypto::SHA256_STR(password);
            if (user.value().get<2>() == password_hash) {
                on_login(user.value().id(), connection, handler);
            } else {
                on_wrong_credentials(connection, handler);
            }
        } else {
            on_wrong_credentials(connection, handler);
        }
    });
}

void DBAuthorizer::register_user(const std::string &nickname,
                                 const std::string &password,
                                 ws_connection_t connection,
                                 authorize_handler handler) {

    db.execute_query([=, this](pqxx::work &tr) {
        std::string password_hash = Crypto::SHA256_STR(password);
        

        try {
            auto user_record = UsersTable::create(tr, nickname, password_hash);

            User &user = user_manager.createUser(user_record.id(), nickname);

            on_register(user, connection, handler);
        } catch(...) {
            on_repeat_login(connection, handler);
        }
    });
}
