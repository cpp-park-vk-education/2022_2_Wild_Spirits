#pragma once

#include <cstdint>
#include <vector>

#include "Action.h"

#ifdef BUILD_LOGIC
#include <GS files>
#else
namespace GS {

    class Action {
    public:
        enum class Cast {
            Tile,
            Self
        };
        enum class Target {
            Both,
            Enemies,
            Allies
        };
    public:
        Action(Cast cast, Target target) : m_Cast(cast), m_Target(target) { }

        Cast castType() const { return m_Cast; }
        Target targetType() const { return m_Target; }
    protected:
        Cast m_Cast;
        Target m_Target;
    };

    class Activatable {
    public:
        Activatable(size_t id) : m_Id(id) { }
        
        std::vector<Action>& actions() { return m_Actions; }
    protected:
        std::vector<Action> m_Actions;
        size_t m_Id;
    };

    class Weapon : public Activatable {
    public:
        Weapon(size_t id) : Activatable(id) { }
    };

    class Spell : public Activatable {
    public:
        Spell(size_t id) : Activatable(id) { }
    };

    class Skill : public Activatable {
    public:
        Skill(size_t id) : Activatable(id) { }
    };

    class Consumable : public Activatable {
    public:
        Consumable(size_t id) : Activatable(id) { }
    };

}
#endif

namespace LM {

    class UseAction : public Action {
    public:
        UseAction(GS::Activatable& activatable, Type type, size_t actionId);

        virtual Type getType() const override;
        
        uint32_t getTargetX() const;
        uint32_t getTargetY() const;

        void setTarget(uint32_t x, uint32_t y);

        GS::Activatable& getActivatable();
        GS::Action::Target getTargetType() const;
        GS::Action::Cast getCastType() const;
        size_t getActionId() const;
    protected:
        GS::Activatable& m_Activatable;
        size_t m_ActionId;
        Type m_Type;

        uint32_t m_TargetX = 0;
        uint32_t m_TargetY = 0;
        //uint32_t m_RangeX;
        //uint32_t m_RangeY;
    };

}
