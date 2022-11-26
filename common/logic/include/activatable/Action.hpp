#pragma once

#include <vector>
#include <cstddef>

#include "Area.hpp"
#include "StatBased.hpp"

class Effect;
class CharacterInstance;

class Action {
 public:
    enum class CastType {
        Self,
        Tile
    };

    struct Result {
     private:
        size_t char_id_;

     public:
        Tile pos = {};
        int hp = 0;
        StatBased::Stats buff;

        explicit Result(size_t char_id) : char_id_(char_id) {}
        explicit Result(size_t char_id, Tile pos, int hp, const StatBased::Stats& buff = {}) :
            char_id_(char_id),
            pos(pos),
            hp(hp),
            buff(buff) {}

        size_t char_id() {
            return char_id_;
        }

        bool operator==(const Result& other) const {
            return false;
        }
    };

 private:
    CastType cast_type_;
    Area* area_;
    unsigned int range_;
    std::vector<Effect*> effects_;

 public:
    Action() = default;
    Action(Area* area, unsigned int range, CastType cast_type, std::vector<Effect*> effects);

    void setCastType(CastType cast_type);

    CastType castType();
    
    void setArea(Area* area);

    const std::vector<Effect*>& effects() const;

    void addEffect(Effect* effect);

    void removeEffect(size_t effect_id);

    std::tuple<std::vector<Result>, ErrorStatus> getResults(const CharacterInstance&, const Tile& tile);

    ~Action();
};
