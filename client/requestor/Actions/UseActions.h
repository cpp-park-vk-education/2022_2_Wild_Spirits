#pragma once

#include <cstdint>
#include <vector>

#include "Action.h"

#include <ActivatableItem.hpp>
#include <Skill.hpp>
#include <Spell.hpp>

namespace LM {

    class UseAction : public Action {
    public:
        UseAction(DnD::ActivatableInterface& activatable, Type type);

        virtual Type getType() const override;

        size_t getTargetX() const;
        size_t getTargetY() const;

        void setTarget(size_t x, size_t y);
        bool isFirstSet() const;

        DnD::ActivatableInterface& getActivatable();
        std::vector<DnD::Action::Target> getTargetTypes() const;
        // DnD::Activatable::Cast getCastType() const;

    protected:
        DnD::ActivatableInterface& m_Activatable;
        Type m_Type;

        size_t m_TargetX = 0;
        size_t m_TargetY = 0;

        bool m_IsFirstSet = true;
    };

}    // namespace LM
