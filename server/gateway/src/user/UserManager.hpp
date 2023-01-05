#pragma once

#include <vector>

#include <User.hpp>

class UserManager {
private:
    std::vector<User> users;

public:
    User *getUser (std::size_t id);

    int createUser (std::string name);
    void deleteUser();
};