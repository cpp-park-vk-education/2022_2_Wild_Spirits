#pragma once

#include <vector>
#include <memory>
#include <cstddef>

#include "Area.hpp"
#include "StatBased.hpp"

namespace DnD {

class Effect;
class CharacterInstance;
class Buff;

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
        std::vector<Buff> buffs;

        explicit Result(size_t char_id);
        Result(size_t char_id, Tile pos, int hp, const std::vector<Buff>& buffs);

        size_t char_id() const {
            return char_id_;
        }

        bool operator==(const Result& other) const {
            return false;
        }

        ~Result();
    };

 private:
    using AreaPtr = std::unique_ptr<Area>;
    using EffectPtr = std::unique_ptr<Effect>;

    CastType cast_type_;
    AreaPtr area_;
    unsigned int range_;
    std::vector<EffectPtr> effects_;

    bool can_miss_ = true;
    std::string target_scaling_ = "dex";

 public:
    Action() = default;
    Action(const Action& other);
    Action& operator=(const Action& other);

    Action(Action&& other);
    Action& operator=(Action&& other);

    void swap(Action& other);

    Action(AreaPtr&& area, std::vector<EffectPtr>&& effects, unsigned int range = 0,
           CastType cast_type = CastType::Tile, bool can_miss = true,
           const std::string& target_scaling = "dex");

    void setCastType(CastType cast_type);
    CastType castType() const;

    void setTargetScaling(const std::string& scaling);
    const std::string& targetScaling() const;

    bool canMiss() const;
    void toggleMissable();
    
    void setArea(AreaPtr&& area);
    AreaPtr& area() const;

    std::vector<EffectPtr>& effects();
    void addEffect(EffectPtr&& effect);
    void removeEffect(size_t effect_id);

    std::tuple<std::vector<Action::Result>, ErrorStatus> getResults(const CharacterInstance&,
                                                            const Tile& tile, uint8_t dice_roll_res = 0);
};
}  // namespace DnD
