#pragma once

#include <Manager.hpp>
#include <User.hpp>

class UserManager: virtual public Manager<User> {
public:
    virtual User &createUser(std::string nickname) = 0;
};

class UserManagerImpl: public UserManager, ManagerImpl<User> {
public:
    virtual User &createUser(std::string nickname) override {
        std::size_t id = id_assigner.assignId();
        entities.emplace(id, User(nickname, id));

        return get(id);
    }
};