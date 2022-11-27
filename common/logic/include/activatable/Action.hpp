#pragma once

#include <vector>
#include <cstddef>

#include "Area.hpp"
#include "StatBased.hpp"
#include "Buff.hpp"

class Effect;
class CharacterInstance;
class Buff;

// TODO: Make ActionResult an inner class like before
struct ActionResult {
    private:
    size_t char_id_;

    public:
    Tile pos = {};
    int hp = 0;
    std::vector<Buff> buffs;

    explicit ActionResult(size_t char_id) : char_id_(char_id) {}
    ActionResult(size_t char_id, Tile pos, int hp, const std::vector<Buff>& buffs);

    size_t char_id() const {
        return char_id_;
    }

    bool operator==(const ActionResult& other) const {
        return false;
    }
};

class Action {
 public:
    enum class CastType {
        Tile,
        Self
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

    std::tuple<std::vector<ActionResult>, ErrorStatus> getResults(const CharacterInstance&,
                                                            const Tile& tile, uint8_t dice_roll_res = 0);

    ~Action();
};
