#pragma once

#include <unordered_map>
#include <cstddef>
#include <functional>
#include <type_traits>

#include "ErrorStatus.hpp"

namespace DnD {
template <typename T>
class Storage {
 private:
    std::unordered_map<size_t, T> data_;

 public:
    using size_type = size_t;

    Storage() = default;
    Storage(const std::unordered_map<size_t, T>& data) : data_(data) {}

    template <typename... Args>
    ErrorStatus add(size_t id, Args&&... args) {
        static_assert(!std::is_pointer<T>::value);
        data_.try_emplace(id, id, std::forward<Args>(args)...);
        return ErrorStatus::Fail();
    }

    ErrorStatus add(T object) {
        if constexpr (std::is_pointer<T>::value) {
            data_.emplace(object->id(), object);
        } else {
            data_.emplace(object.id(), object);
        }
        return ErrorStatus::Fail();
    }

    ErrorStatus remove(size_t id) {
        data_.erase(id);
        return ErrorStatus::Fail();
    }

    T& get(size_t id) {
        return data_.find(id)->second;
    }

    size_t size() const {
        return data_.size();
    }

    auto begin() {
        return data_.begin();
    }

    auto end() {
        return data_.end();
    }

    void each(const std::function<void(T&)>& visit) {
        for (auto& [_, elem] : data_) {
            visit(elem);
        }
    }
};
}  // namespace DnD
