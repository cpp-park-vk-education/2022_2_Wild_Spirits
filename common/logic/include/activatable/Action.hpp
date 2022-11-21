#pragma once

#include <vector>

#include "Effect.hpp"
#include "Area.hpp"

class Action {
 public:
    enum class CastType {
        Self,
        Tile
    };

    class Result {
     private:
        std::vector<Effect::Result> results_;
     public:
        std::string serialize() {
            return "";
        }
    };

 private:
    CastType cast_type_;
    Area* area_;
    unsigned int range_;
    std::vector<Effect*> effects_;

 public:
    Action(Area* area, unsigned int range, CastType cast_type, std::vector<Effect*> effects) :
        cast_type_(cast_type), area_(area), range_(range), effects_(effects) {}
    
    void setCastType(CastType cast_type) {
        cast_type_ = cast_type;
    }

    CastType castType() {
        return cast_type_;
    }

    void setArea(Area* area) {
        delete area_;
        area_ = area;
    }

    void addEffect(Effect* effect) {
        effects_.push_back(effect);
    }

    void removeEffect(size_t effect_id) {
        effects_.erase(effects_.begin() + effect_id);
    }

    Result getResult(const CharacterInstance&, const Tile& tile) {
        return Result{};
    }

    ~Action() {
        delete area_;
        for (auto effect : effects_) {
            delete effect;
        }
    }
};
