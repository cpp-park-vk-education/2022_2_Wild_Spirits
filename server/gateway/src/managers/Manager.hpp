#pragma once

#include <unordered_map>
#include <IdAssigner.hpp>

template <typename T>
class Manager {
public:
    virtual T &get(std::size_t id) = 0;

    virtual void remove(std::size_t id) = 0;
};

template <typename T>
class ManagerImpl: virtual public Manager<T> {
protected:
    std::unordered_map<std::size_t, T> entities;
    ReuseIdAssigner id_assigner;

public:
    virtual T &get(std::size_t id) override;

    virtual void remove(std::size_t id) override;
};

template <typename T>
T &ManagerImpl<T>::get(std::size_t id) {
    return entities.find(id)->second;
}

template <typename T>
void ManagerImpl<T>::remove(std::size_t id) {
    entities.erase(id);
    id_assigner.releaseId(id);
}
