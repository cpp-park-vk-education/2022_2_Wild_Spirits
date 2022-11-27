#include "Effect.hpp"
#include "Buff.hpp"
#include "Damage.hpp"

#include "Action.hpp"

void Heal::updateActionResult(const CharacterInstance& character, ActionResult* result) const {}

void Move::updateActionResult(const CharacterInstance& character, ActionResult* result) const {}

void DealDamage::updateActionResult(const CharacterInstance& character, ActionResult* result) const {}

void Buff::updateActionResult(const CharacterInstance& character, ActionResult* result) const {}
