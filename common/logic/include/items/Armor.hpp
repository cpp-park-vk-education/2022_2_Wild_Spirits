#pragma once

#include "Item.hpp"

namespace DnD {
class Armor : public Item {
 public:
    enum class Type {
        Light,
        Medium,
        Heavy
    };

 private:
    unsigned int defense_;
    Type type_;

 public:
    Armor() = default;
    Armor(size_t id, std::string_view name, int image_id, int cost,
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
};
}  // namespace DnD
