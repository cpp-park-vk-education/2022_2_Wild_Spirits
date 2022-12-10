#pragma once

#include <unordered_map>

#include <User.hpp>
#include <IdAssigner.hpp>

class UserManager {
public:
    virtual User &getUser(std::size_t id) = 0;

    virtual User &createUser(std::string nickname) = 0;
    virtual void deleteUser(std::size_t id) = 0;
};

class UserManagerImpl: public UserManager {
private:
    std::unordered_map<std::size_t, User> users;
    ReuseIdAssigner id_assigner;

public:
    virtual User &getUser(std::size_t id) override;

    virtual User &createUser(std::string nickname) override;
    virtual void deleteUser(std::size_t id) override;
};
