#pragma once

#include <cstdint>
#include <vector>

#include "Action.h"

#ifdef BUILD_LOGIC
    #include <ActivatableItem.hpp>
    #include <Skill.hpp>
    #include <Spell.hpp>
#else
namespace DnD {

    class Action {
    public:
        enum class Target { Both, Enemies, Allies };

    public:
        explicit Action(Target target) : m_Target(target) { }

        Target targetType() const { return m_Target; }

    protected:
        Target m_Target;
    };

    class ActivatableInterface {
    public:
        enum class Cast { Tile, Self };

    public:
        ActivatableInterface(size_t id, Cast cast) : m_Id(id), m_Cast(cast) { }

        Cast castType() const { return m_Cast; }
        std::vector<Action>& actions() { return m_Actions; }

    protected:
        size_t m_Id;
        Cast m_Cast;
        std::vector<Action> m_Actions;
    };

    class Weapon : public ActivatableInterface {
    public:
        Weapon(size_t id, Cast cast) : ActivatableInterface(id, cast) { }
    };

    class Spell : public ActivatableInterface {
    public:
        Spell(size_t id, Cast cast) : ActivatableInterface(id, cast) { }
    };

    class Skill : public ActivatableInterface {
    public:
        Skill(size_t id, Cast cast) : ActivatableInterface(id, cast) { }
    };

    class Consumable : public ActivatableInterface {
    public:
        Consumable(size_t id, Cast cast) : ActivatableInterface(id, cast) { }
    };

}    // namespace DnD
#endif

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
        DnD::ActivatableInterface::Cast getCastType() const;

    protected:
        DnD::ActivatableInterface& m_Activatable;
        Type m_Type;

        size_t m_TargetX = 0;
        size_t m_TargetY = 0;

        bool m_IsFirstSet = true;
    };

}    // namespace LM
