#pragma once

#include <cstdint>
#include <vector>

#include "Action.h"

#ifdef BUILD_LOGIC
#include <GS files>
#else
namespace DnD {

    class Action {
    public:
        enum class Target {
            Both,
            Enemies,
            Allies
        };
    public:
        Action(Target target) : m_Target(target) { }

        Target targetType() const { return m_Target; }
    protected:
        Target m_Target;
    };

    class Activatable {
    public:
        enum class Cast {
            Tile,
            Self
        };
    public:
        Activatable(size_t id, Cast cast) : m_Id(id), m_Cast(cast) { }
        
        Cast castType() const { return m_Cast; }
        std::vector<Action>& actions() { return m_Actions; }
    protected:
        size_t m_Id;
        Cast m_Cast;
        std::vector<Action> m_Actions;
    };

    class Weapon : public Activatable {
    public:
        Weapon(size_t id, Cast cast) : Activatable(id, cast) { }
    };

    class Spell : public Activatable {
    public:
        Spell(size_t id, Cast cast) : Activatable(id, cast) { }
    };

    class Skill : public Activatable {
    public:
        Skill(size_t id, Cast cast) : Activatable(id, cast) { }
    };

    class Consumable : public Activatable {
    public:
        Consumable(size_t id, Cast cast) : Activatable(id, cast) { }
    };

}
#endif

namespace LM {

    class UseAction : public Action {
    public:
        UseAction(DnD::Activatable& activatable, Type type);

        virtual Type getType() const override;
        
        size_t getTargetX() const;
        size_t getTargetY() const;

        void setTarget(size_t x, size_t y);
        bool isFirstSet() const;

        DnD::Activatable& getActivatable();
        std::vector<DnD::Action::Target> getTargetTypes() const;
        DnD::Activatable::Cast getCastType() const;
    protected:
        DnD::Activatable& m_Activatable;
        Type m_Type;

        size_t m_TargetX = 0;
        size_t m_TargetY = 0;
        //uint32_t m_RangeX;
        //uint32_t m_RangeY;

        bool m_IsFirstSet = true;
    };

}
