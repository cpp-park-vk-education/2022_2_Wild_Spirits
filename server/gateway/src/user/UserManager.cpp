#include <UserManager.hpp>

User &UserManagerImpl::getUser(std::size_t id) {
    return users.find(id)->second;
}

User &UserManagerImpl::createUser(std::string nickname) {
    std::size_t id = id_assigner.assignId();
    users.emplace(id, User(nickname, id));

    return getUser(id);
}

void UserManagerImpl::deleteUser(std::size_t id) {
    users.erase(id);
    id_assigner.releaseId(id);
}
