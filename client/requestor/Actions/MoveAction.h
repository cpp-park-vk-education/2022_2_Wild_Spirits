#include "Action.h"

namespace LM {

    class MoveAction : public Action {
    public:
        MoveAction(size_t x, size_t y);

        virtual Type getType() const override;

        uint32_t getTargetX() const;
        uint32_t getTargetY() const;

        void setTarget(uint32_t x, uint32_t y);
    protected:
        uint32_t m_TargetX = 0;
        uint32_t m_TargetY = 0;

    };

}
