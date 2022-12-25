#pragma once

#include <string>
#include <cstdint>

namespace DnD {
class DamageType {
 private:
    uint8_t id_;
    std::string name_;

 public:
    explicit DamageType(uint8_t id, const std::string& name = "") : id_(id), name_(name) {}

    uint8_t id() const {
        return id_;
    }

    const std::string& name() const {
        return name_;
    }
};
}  // namespace DnD
