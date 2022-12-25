#pragma once

#include "Item.hpp"

namespace DnD {
class Armor : public Item {
 public:
    static constexpr const char* kScaling = "dex";
    static constexpr int8_t kMaxBonus = 2;

    enum class Type {
        Light,
        Medium,
        Heavy
    };

 private:
    unsigned int defense_ = 10;
    Type type_ = Type::Medium;

 public:
    Armor() = default;

    Armor(size_t id) : Item(id) {}

    Armor(size_t id, std::string_view name, size_t image_id, int cost,
          unsigned int defense, Type type, const Info& info = {}) :
        Item(id, name, image_id, cost, info), defense_(defense), type_(type) {}

    unsigned int defense() const {
        return defense_;
    }

    void setDefense(int defense) {
        defense_ = defense;
    }

    Type armorType() const {
        return type_;
    }

    void setArmorType(Type type) {
        type_ = type;
    }

    ErrorStatus setCharacteristic(const std::string& which, const SetterParam& to) override;
};
}  // namespace DnD
