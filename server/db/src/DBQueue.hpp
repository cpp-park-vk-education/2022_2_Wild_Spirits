#pragma once

#include <boost/asio.hpp>
#include <pqxx/pqxx>
#include <functional>
#include <string>

using get_db_handler = std::function<void(pqxx::result)>;
using create_db_handler = std::function<void(std::size_t)>;

class DBQueue {
public:
    virtual void getUser (std::string name, get_db_handler) = 0;
    virtual void createUser (std::string name, std::string password, create_db_handler) = 0;

    virtual void getCharacter (std::size_t id, get_db_handler) = 0;
    virtual void createCharacter (create_db_handler) = 0;

    virtual void getCharacterInstance (std::size_t id, get_db_handler) = 0;
    virtual void createCharacterInstance (create_db_handler) = 0;

    virtual void getLocation (std::size_t id, get_db_handler) = 0;
    virtual void createLocation (create_db_handler) = 0;

    virtual void getCampaign (std::size_t id, get_db_handler) = 0;
    virtual void createCampaign (create_db_handler) = 0;

    virtual void loadCampaign (std::size_t id, get_db_handler) = 0;
};

class AsioDBQueue: public DBQueue {
private:
    boost::asio::thread_pool pool;

public:
    AsioDBQueue(std::size_t threads);

    virtual void getUser (std::string name, get_db_handler) override;
    virtual void createUser (std::string name, std::string password, create_db_handler) override;

    virtual void getCharacter (std::size_t id, get_db_handler) override;
    virtual void createCharacter (create_db_handler) override;

    virtual void getCharacterInstance (std::size_t id, get_db_handler) override;
    virtual void createCharacterInstance (create_db_handler) override;

    virtual void getLocation (std::size_t id, get_db_handler) override;
    virtual void createLocation (create_db_handler) override;

    virtual void getCampaign (std::size_t id, get_db_handler) override;
    virtual void createCampaign (create_db_handler) override;

    virtual void loadCampaign (std::size_t id, get_db_handler) override;
};