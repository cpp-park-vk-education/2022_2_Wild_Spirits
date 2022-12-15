#pragma once

#include "Action.h"

namespace LM {

    class MoveAction: public Action {
    public:
        MoveAction(size_t x, size_t y);

        virtual Type getType() const override;

        size_t getTargetX() const;
        size_t getTargetY() const;

        void setTarget(size_t x, size_t y);
    protected:
        size_t m_TargetX = 0;
        size_t m_TargetY = 0;
    };

}    // namespace LM
