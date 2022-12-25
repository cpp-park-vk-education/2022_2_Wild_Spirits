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

    class ImageGetter {
    public:
        explicit ImageGetter(size_t imageId) : m_ImageId(imageId) { }
        size_t getImageId() const { return m_ImageId; }

    protected:
        size_t m_ImageId;
    };

    class ActivatableInterface : public ImageGetter {
    public:
        enum class Cast { Tile, Self };

    public:
        ActivatableInterface(size_t id, Cast cast, size_t imageId)
            : ImageGetter(imageId),
              m_Id(id),
              m_Cast(cast) { }

        size_t getImageId() const { return m_ImageId; }

        Cast castType() const { return m_Cast; }
        std::vector<Action>& actions() { return m_Actions; }

    protected:
        size_t m_Id;
        Cast m_Cast;
        std::vector<Action> m_Actions;
    };

    class Weapon : public ActivatableInterface {
    public:
        Weapon(size_t id, Cast cast, size_t imageId) : ActivatableInterface(id, cast, imageId) { }
    };

    class Spell : public ActivatableInterface {
    public:
        Spell(size_t id, Cast cast, size_t imageId) : ActivatableInterface(id, cast, imageId) { }
    };

    class Skill_Instance : public ActivatableInterface {
    public:
        Skill_Instance(size_t id, Cast cast, size_t imageId) : ActivatableInterface(id, cast, imageId) { }
    };

    class Consumable : public ActivatableInterface {
    public:
        Consumable(size_t id, Cast cast, size_t imageId) : ActivatableInterface(id, cast, imageId) { }
    };

}    // namespace DnD
#endif

namespace LM {

    class UseAction : public Action {
    public:
        UseAction(const DnD::ActivatableInterface& activatable, Type type);

        virtual Type getType() const override;

        size_t getTargetX() const;
        size_t getTargetY() const;

        void setTarget(size_t x, size_t y);
        bool isFirstSet() const;

        const DnD::ActivatableInterface& getActivatable() const;
        std::vector<DnD::Action::Target> getTargetTypes() const;
        DnD::ActivatableInterface::Cast getCastType() const;

    protected:
        const DnD::ActivatableInterface& m_Activatable;
        Type m_Type;

        size_t m_TargetX = 0;
        size_t m_TargetY = 0;

        bool m_IsFirstSet = true;
    };

}    // namespace LM
