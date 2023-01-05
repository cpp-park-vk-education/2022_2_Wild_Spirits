#include "Effect.hpp"
#include "Buff.hpp"
#include "Damage.hpp"

#include "Action.hpp"

namespace DnD {
void Heal::updateActionResult(const CharacterInstance& character, Action::Result* result) const {}

void Move::updateActionResult(const CharacterInstance& character, Action::Result* result) const {}

void DealDamage::updateActionResult(const CharacterInstance& character, Action::Result* result) const {}

void Buff::updateActionResult(const CharacterInstance& character, Action::Result* result) const {}
}  // namespace DnD
