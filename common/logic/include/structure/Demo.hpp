#pragma once

#include "GameState.hpp"
#include "GameMap.hpp"

namespace DnD {
    class DemoLogicProcessor : public LogicProcessorImpl {
    public:
        DemoLogicProcessor();
    };

    class DemoGameMap : public GameMapImpl {
    public:
        DemoGameMap(GameState& game);
    };
}  // namespace DnD
