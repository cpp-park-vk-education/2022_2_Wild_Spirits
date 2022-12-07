#include "Effect.hpp"
#include "Buff.hpp"
#include "Damage.hpp"

#include "Action.hpp"
#include "CharacterInstance.hpp"

#include <numeric>
#include <sstream>

namespace DnD {
void Heal::updateActionResult(const CharacterInstance&, Action::Result* result) const {
    result->hp += amount_;
}

void Move::updateActionResult(const CharacterInstance& character, Action::Result* result) const {
    result->pos += offset_;
    // TODO: Make offset depend on relative positions of interacting characters
}

void DealDamage::updateActionResult(const CharacterInstance& character, Action::Result* result) const {
    auto roll_results = dice_->roll(die_type_, times_);
    float damage_modifier = character.damageModifier(damage_type_.id());

    result->hp -= std::accumulate(roll_results.begin(), roll_results.end(), 0) * damage_modifier;
    // TODO: Store roll results in ActionResult
}

void Buff::updateActionResult(const CharacterInstance&, Action::Result* result) const {
    result->buffs.push_back(*this);
}

std::string Buff::statsToStr() const {
    std::stringstream out;
    out << std::showpos;
    for (const auto& [stat, value] : stats()) {
        out << stat << ": " << static_cast<int>(value) << '\n';
    }
    return out.str();
}

std::ostream& operator<<(std::ostream& out, const Buff& buff) {
    out << "{ turns: " << buff.turnsLeft() << ", { ";
    for (const auto& [stat, value] : buff.stats()) {
        out << stat << ": " << static_cast<int>(value) << ", ";
    }
    return out << "} }";
}
}  // namespace DnD
