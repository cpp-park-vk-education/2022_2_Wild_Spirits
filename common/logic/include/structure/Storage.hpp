#pragma once

#include <map>
#include <memory>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <concepts>
#include <iterator>

#include "ErrorStatus.hpp"
#include "Exception.hpp"
#include "Print.hpp"

namespace DnD {

template <typename T>
concept IdentifiablePtr = requires(T obj) {
    { obj->id() } -> std::unsigned_integral;
};

template <typename T>
concept IdentifiableObj = requires(T obj) {
    { obj.id() } -> std::unsigned_integral;
};

template <typename T>
concept IdentifiableEntity = IdentifiablePtr<T> || IdentifiableObj<T>;

template <typename T, typename U>
concept DerivedPtr = requires(T obj) {
    { *obj } -> std::derived_from<U>;
};

template <typename T, typename U>
concept DerivedFrom = std::derived_from<T, U> || DerivedPtr<T, U>;

class OutOfRange : public Exception {
 public:
    OutOfRange() :
        Exception("Storage index out of range") {}
};

template <IdentifiableEntity T>
class Storage {
 private:
    std::unordered_map<size_t, T> data_;

 protected:
    static constexpr size_t kMaxSize = 64;

 public:
    using size_type = size_t;
    using iterator = typename decltype(data_)::iterator;
    using const_iterator = typename decltype(data_)::const_iterator;

    Storage() = default;
    Storage(const std::unordered_map<size_t, T>& data) : data_(data) {}
    Storage(std::unordered_map<size_t, T>&& data) : data_(std::move(data)) {}

    Storage(const std::vector<T>& data) : Storage(data.begin(), data.end()) {}

    Storage(std::vector<T>&& data) : Storage(std::make_move_iterator(data.begin()),
                                             std::make_move_iterator(data.end())) {}

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
    std::tuple<T*, ErrorStatus> add(size_t id, Args&&... args) requires IdentifiableObj<T> {
        if (size() >= kMaxSize) {
            return std::make_tuple(nullptr, ErrorStatus::STORAGE_FULL);
        }

        auto [it, inserted] = data_.try_emplace(id, id, std::forward<Args>(args)...);
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
    }

    std::tuple<T*, ErrorStatus> add(const T& object) requires IdentifiableObj<T> {
        if (size() >= kMaxSize) {
            return std::make_tuple(nullptr, ErrorStatus::STORAGE_FULL);
        }

        auto [it, inserted] = data_.emplace(object.id(), object);
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
    }

    std::tuple<T*, ErrorStatus> add(T&& object) requires IdentifiableObj<T> {
        if (size() >= kMaxSize) {
            return std::make_tuple(nullptr, ErrorStatus::STORAGE_FULL);
        }

        auto [it, inserted] = data_.emplace(object.id(), std::move(object));
        return inserted ? std::make_tuple(&it->second, ErrorStatus::OK) :
                          std::make_tuple(nullptr, ErrorStatus::ALREADY_EXISTS);
    }

    std::tuple<T, ErrorStatus> add(T object) requires IdentifiablePtr<T> {
        auto [it, inserted] = data_.emplace(object->id(), object);
        return inserted ? std::make_tuple(it->second, ErrorStatus::OK) :
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

    static constexpr size_t maxsize() {
        return kMaxSize;
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

    bool wasUpdated() const requires DerivedFrom<T, GameEntityInterface> {
        for (auto& [_, elem] : data_) {
            if constexpr(DerivedPtr<T, GameEntityInterface>) {
                if (elem->wasUpdated()) {
                    return true;
                }
            } else {
                if (elem.wasUpdated()) {
                    return true;
                }
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Storage& storage) {
        return printIterable(storage.begin(), storage.end(), out,
                             [] (std::pair<size_t, T> it, std::ostream& out) { out << it.second; });
    }
};

template <IdentifiableEntity T>
class SharedStorage : public Storage<std::shared_ptr<T>> {
 public:
    using Storage<std::shared_ptr<T>>::add;

    template <typename... Args>
    std::tuple<T*, ErrorStatus> add(size_t id, Args&&... args) {
        auto [shared, status] = add(std::make_shared<T>(id, std::forward<Args>(args)...));
        return shared ? std::make_tuple(shared.get(), status) :
                        std::make_tuple(nullptr, status);
    }

    std::tuple<T*, ErrorStatus> add(const T& object) {
        if (this->size() >= this->kMaxSize) {
            return std::make_tuple(nullptr, ErrorStatus::STORAGE_FULL);
        }

        auto [shared, status] = add(std::make_shared<T>(object));
        return shared ? std::make_tuple(shared.get(), status) :
                        std::make_tuple(nullptr, status);
    }

    std::tuple<T*, ErrorStatus> add(T&& object) {
        if (this->size() >= this->kMaxSize) {
            return std::make_tuple(nullptr, ErrorStatus::STORAGE_FULL);
        }

        auto [shared, status] = add(std::make_shared<T>(std::move(object)));
        return shared ? std::make_tuple(shared.get(), status) :
                        std::make_tuple(nullptr, status);
    }

    T& get(size_t id) {
        auto shared = Storage<std::shared_ptr<T>>::get(id);
        return *shared;
    }

    std::shared_ptr<T> safeGet(size_t id) noexcept {
        auto shared = Storage<std::shared_ptr<T>>::safeGet(id);
        return shared ? *shared : nullptr;
    }

    const T& get(size_t id) const {
        return const_cast<const T&>(const_cast<SharedStorage*>(this)->get(id));
    }

    std::shared_ptr<const T> safeGet(size_t id) const noexcept {
        return const_cast<const T*>(const_cast<SharedStorage*>(this)->safeGet(id));
    }

    void each(const std::function<void(T&)>& visit) {
        for (auto& [_, elem] : *this) {
            visit(*elem);
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const SharedStorage& storage) {
        return printIterable(storage.begin(), storage.end(), out,
                             [] (std::pair<size_t, T> it, std::ostream& out) { out << *(it.second); });
    }
};
}  // namespace DnD
