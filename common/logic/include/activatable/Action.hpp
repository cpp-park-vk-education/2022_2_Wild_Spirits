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
        Tile,
        Self
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
    Area* area_ = nullptr;
    unsigned int range_;
    std::vector<Effect*> effects_;

    bool can_miss_ = true;
    std::string target_scaling_ = "dex";

 public:
    Action() = default;
    Action(const Action& other);
    Action& operator=(const Action& other);

    Action(Action&& other);
    Action& operator=(Action&& other);

    void swap(Action& other);

    Action(Area* area, const std::vector<Effect*>& effects, unsigned int range = 0,
           CastType cast_type = CastType::Tile, bool can_miss = true,
           const std::string& target_scaling = "dex");

    void setCastType(CastType cast_type);
    CastType castType() const;

    void setTargetScaling(const std::string& scaling);
    const std::string& targetScaling() const;

    bool canMiss() const;
    void toggleMissable();
    
    void setArea(Area* area);
    const Area* area() const;

    std::vector<Effect*>& effects();
    void addEffect(Effect* effect);
    void removeEffect(size_t effect_id);

    std::tuple<std::vector<Result>, ErrorStatus> getResults(const CharacterInstance&,
                                                            const Tile& tile, uint8_t dice_roll_res = 0);

    ~Action();
};
