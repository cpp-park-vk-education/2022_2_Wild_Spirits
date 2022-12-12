#pragma once

#include <vector>
#include <list>
#include <memory>
#include <cstddef>

#include "Area.hpp"
#include "Armor.hpp"
#include "Dice.hpp"
#include "Storage.hpp"
#include "StatBased.hpp"

namespace DnD {

class Effect;
class CharacterInstance;
class Buff;

class Action {
 public:
    enum class Target {
        Both,
        Enemies,
        Allies
    };

    struct Result {
     private:
        size_t char_id_;

     public:
        Tile pos = {};
        int hp = 0;
        std::list<Buff> buffs;
        std::vector<Dice::Roll> roll_results;

        explicit Result(size_t char_id);
        Result(size_t char_id, Tile pos, int hp, const std::list<Buff>& buffs,
               const std::vector<Dice::Roll>& roll_res = {});

        size_t id() const {
            return char_id_;
        }

        bool operator==(const Result& other) const;
        Result& operator+=(Result&& other);

        friend std::ostream& operator<<(std::ostream& out, const Result& result);
    };

 private:
    using AreaPtr = std::unique_ptr<Area>;
    using EffectPtr = std::unique_ptr<Effect>;

    Target target_type_;

    AreaPtr area_;
    unsigned int range_;
    std::vector<EffectPtr> effects_;

    bool can_miss_ = true;
    std::string target_scaling_ = Armor::kScaling;

    template <typename T>
    void applyEffectsTo(SharedStorage<T>& characters, std::vector<Action::Result>* results, uint8_t dice_roll_res = 0,
                    std::function<bool(const CharacterInstance&)> predicate = [] (const auto&) { return true; }) const;

 public:
    Action() = default;
    Action(const Action& other);
    Action& operator=(const Action& other);

    Action(Action&& other);
    Action& operator=(Action&& other);

    void swap(Action& other);

    Action(AreaPtr&& area, std::vector<EffectPtr>&& effects,
           Target target_type = Target::Both, unsigned int range = 0,
           bool can_miss = true,
           const std::string& target_scaling = "dex");

    void setTargetType(Target cast_type);
    Target targetType() const;

    void setTargetScaling(const std::string& scaling);
    const std::string& targetScaling() const;

    bool canMiss() const;
    void toggleMissable();
    
    void setArea(AreaPtr&& area);
    const AreaPtr& area() const;

    std::vector<EffectPtr>& effects();
    void addEffect(EffectPtr&& effect);
    void removeEffect(size_t effect_id);

    std::tuple<std::vector<Action::Result>, ErrorStatus> getResults(const CharacterInstance&,
                                                            const Tile& tile, uint8_t dice_roll_res = 0) const;
};
}  // namespace DnD
