#pragma once

#include <memory>
#include <string>
#include <vector>

class Gateway;

class User;

class RequestProcessor {};

class Room {
protected:
    std::size_t _id;
    RequestProcessor processor;
    Gateway &gateway;

public:
    Room(std::size_t id, Gateway &gateway): _id(id), gateway(gateway) {}

    virtual void addUser(User*) = 0;

    virtual void sendDM(const std::string&) = 0 ;
    virtual void broadcast(const std::string&) = 0;

    std::size_t id() const {
        return _id;
    }

    // virtual void sendImageTo(const std::string&, std::size_t) = 0;
    virtual void processRequest(std::size_t user_id, const std::string &request) = 0;
};