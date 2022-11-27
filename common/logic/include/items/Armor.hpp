#pragma once

#include "Item.hpp"

class Armor : public Item {
 public:
    enum class Type {
        Light,
        Medium,
        Heavy
    };

 private:
    int defense_;
    Type type_;

 public:
    Armor() = default;
    Armor(std::string_view name, int image_id, int cost,
          int defense, Type type, const Info& info = {}) :
        Item(name, image_id, cost, info), defense_(defense), type_(type) {}

    int defense() const {
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
