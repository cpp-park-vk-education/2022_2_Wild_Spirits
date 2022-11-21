#pragma once

#include <cstdlib>
#include <string>
#include <vector>

class RequestProcessor {};

class Room {
private:
    RequestProcessor processor;

public:
    virtual void sendDM (std::string) = 0 ;
    virtual void broadcast (std::string) = 0;

    virtual void sendImageTo (std::string, std::size_t) = 0;
    virtual void processRequest (std::size_t user_id, std::string request) = 0;
};

class RoomImpl: public Room {
private:
    std::vector<std::size_t> playerIds;
    std::size_t DMId;

public:
    virtual void sendDM (std::string) override;
    virtual void broadcast (std::string) override;

    virtual void sendImageTo (std::string, std::size_t) override;
    virtual void processRequest (std::size_t user_id, std::string request) override;
};
