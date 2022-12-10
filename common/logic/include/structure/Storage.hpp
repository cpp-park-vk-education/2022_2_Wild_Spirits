#pragma once

#include <map>
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
    std::unordered_map<size_t, stT> data_;

 public:
    using size_type = size_t;
    using iterator = typename decltype(data_)::iterator;
    using const_iterator = typename decltype(data_)::const_iterator;

    Storage() = default;
    Storage(const std::unordered_map<size_t, T>& data) : data_(data) {}

    Storage(const Storage& other) : data_(other.data_) {}
    Storage(Storage&& other) : data_(std::move(other.data_)) {}

    Storage& operator=(const Storage& other) {
        auto tmp = other;
        std::swap(data_, tmp.data_);
        return *this;
    }

    Storage& operator=(Storage&& other) {
        auto tmp = std::move(other);
        std::swap(data_, tmp.data_);
        return *this;
    }

    template <std::forward_iterator Iter>
    Storage(Iter begin, Iter end) {
        for (auto it = begin; it != end; it = std::next(it)) {
            add(*it);
        }
    }

    template <typename... Args>
    std::tuple<T*, ErrorStatus> add(size_t id, Args&&... args) requires (!std::is_pointer_v<T>) {
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

        auto& [it, inserted] = result;
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
    }

    std::tuple<T*, ErrorStatus> add(T&& object) requires (!std::is_pointer_v<T>) {
        auto [it, inserted] = data_.try_emplace(object.id(), std::move(object));
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
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

    const T& get(size_t id) const {
        return const_cast<const T&>(const_cast<Storage*>(this)->get(id));
    }

    const T safeGet(size_t id) const noexcept requires std::is_pointer_v<T> {
        return const_cast<const T>(const_cast<Storage*>(this)->safeGet(id));
    }

    const T* safeGet(size_t id) const noexcept {
        return const_cast<const T*>(const_cast<Storage*>(this)->safeGet(id));
    }

    bool contains(size_t id) const {
        return safeGet(id) != nullptr;
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
        for (auto it = storage.data_.begin(), end = storage.data_.end(); it != end; ++it) {
            out << it->second;
            if (std::next(it) != end) {
                out << ", ";
            }
        }
        return out;
    }
};
}  // namespace DnD
