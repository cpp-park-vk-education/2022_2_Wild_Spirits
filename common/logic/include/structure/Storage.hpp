#pragma once

#include <map>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <iterator>

#include "ErrorStatus.hpp"
#include "Exception.hpp"

namespace DnD {
template <typename T>
class Storage {
 private:
    std::unordered_map<size_t, T> data_;

 public:
    using size_type = size_t;
    using iterator = typename decltype(data_)::iterator;
    using const_iterator = typename decltype(data_)::const_iterator;

    Storage() = default;
    Storage(const std::unordered_map<size_t, T>& data) : data_(data) {}
    
    template <std::forward_iterator Iter>
    Storage(Iter begin, Iter end) {
        for (auto it = begin; it != end; it = std::next(it)) {
            add(*it);
        }
    }

    template <typename... Args>
    std::tuple<T*, ErrorStatus> add(size_t id, Args&&... args) {
        static_assert(!std::is_pointer<T>::value);
        auto [it, inserted] = data_.try_emplace(id, id, std::forward<Args>(args)...);
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
    }

    std::tuple<T*, ErrorStatus> add(const T& object) {
        std::pair<iterator, bool> result;
    
        if constexpr (std::is_pointer<T>::value) {
            result = data_.emplace(object->id(), object);
        } else {
            result =  data_.emplace(object.id(), object);
        }
        
        auto& [iter, inserted] = result;
        return inserted ? std::make_tuple(&iter->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
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

    T safeGet(size_t id) noexcept requires std::is_pointer_v<T> {
        auto it = data_.find(id);
        if (it == data_.end()) {
            return nullptr;
        }
        return it->second;
    }
    
    T* safeGet(size_t id) noexcept {
        auto it = data_.find(id);
        if (it == data_.end()) {
            return nullptr;
        }
        return &it->second;
    }

    size_t size() const {
        return data_.size();
    }

    iterator begin() {
        return data_.begin();
    }

    iterator end() {
        return data_.end();
    }

    const_iterator begin() const {
        return data_.cbegin();
    }

    const_iterator end() const {
        return data_.cend();
    }

    void each(const std::function<void(T&)>& visit) {
        for (auto& [_, elem] : data_) {
            visit(elem);
        }
    }

    bool operator==(const Storage& other) const {
        return data_ == other.data_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Storage& storage) {
        for (const auto& [_, obj] : storage.data_) {
            out << obj << " ";
        }
        return out;
    }
};
}  // namespace DnD
