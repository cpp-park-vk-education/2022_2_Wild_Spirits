#pragma once

#include <unordered_map>
#include <cstddef>
#include <tuple>

#include "Utils.hpp"

template <typename T>
class Storage {
 private:
    std::unordered_map<size_t, T> data_;

 public:
    template <typename... T>
    ErrorStatus add(size_t id, T... args) {
        data_.try_emplace(id, args...);
        return ErrorStatus::Fail;
    }

    ErrorStatus remove(size_t id) {
        data_.erase(id);
        return ErrorStatus::Fail;
    }

    std::tuple<T&, ErrorStatus> get(size_t id) {
        return {T{}, ErrorStatus::Fail};
    }
};
