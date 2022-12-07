#pragma once

#include <unordered_map>
#include <map>
#include <cstddef>
#include <functional>
#include <type_traits>

#include "ErrorStatus.hpp"
#include "Exception.hpp"

namespace DnD {
class PlayerCharacter;
template <typename T>
concept Identifiable = requires(T&& obj) {
    { obj.id() } -> std::unsigned_integral;
} || requires(T&& obj) {
    { obj->id() } -> std::unsigned_integral;
} || std::is_same<T, PlayerCharacter>::value;

template <Identifiable T>
class Storage {
 private:
    std::map<size_t, T> data_;

 public:
    using size_type = size_t;

    Storage() = default;
    // Storage(const std::unordered_map<size_t, T>& data) : data_(data) {}
    Storage(const std::map<size_t, T>& data) : data_(data) {}

    template <typename... Args>
    ErrorStatus add(size_t id, Args&&... args) {
        static_assert(!std::is_pointer<T>::value);
        auto [_, inserted] = data_.try_emplace(id, id, std::forward<Args>(args)...);
        return inserted ? ErrorStatus::OK : ErrorStatus::ALREADY_EXISTS;
    }

    ErrorStatus add(T object) {
        std::pair<typename decltype(data_)::iterator, bool> result;
    
        if constexpr (std::is_pointer<T>::value) {
            result = data_.emplace(object->id(), object);
        } else {
            result =  data_.emplace(object.id(), object);
        }

        return result.second ? ErrorStatus::OK : ErrorStatus::ALREADY_EXISTS;
    }

    ErrorStatus remove(size_t id) {
        auto erased = data_.erase(id);
        return erased ? ErrorStatus::OK : ErrorStatus::NO_SUCH_ITEM;
    }

    T& get(size_t id) {
        auto it = data_.find(id);
        if (it == data_.end()) {
            throw OutOfRange();
        }
        return it->second;
    }

    std::tuple<T*, ErrorStatus> safeGet(size_t id) noexcept {
        auto it = data_.find(id);
        if (it == data_.end()) {
            return std::make_tuple(nullptr, ErrorStatus::NO_SUCH_ITEM);
        }
        return std::make_tuple(&it->second, ErrorStatus::OK);
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
