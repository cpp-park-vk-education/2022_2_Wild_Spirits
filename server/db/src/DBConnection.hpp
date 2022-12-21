#pragma once

#include <pqxx/pqxx>

class DBConnection {
private:
    pqxx::connection connection;
public:
    DBConnection (const std::string &options);

    pqxx::result getUser (std::string name);
    std::size_t createUser (std::string name, std::string password);

    pqxx::result getCharacter (std::size_t id);
    std::size_t createCharacter ();

    pqxx::result getCharacterInstance (std::size_t id);
    std::size_t createCharacterInstance ();

    pqxx::result getLocation (std::size_t id);
    std::size_t createLocation ();

    pqxx::result getCampaign (std::size_t id);
    std::size_t createCampaign ();

    pqxx::result loadCampaign (std::size_t id);
};