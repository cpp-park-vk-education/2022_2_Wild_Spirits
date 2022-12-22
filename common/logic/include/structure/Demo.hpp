#pragma once

#include "GameState.hpp"
#include "GameMap.hpp"

namespace DnD {
    class DemoLogicProcessor : public LogicProcessorImpl {
        DemoLogicProcessor();
    };

    class DemoGameMap : public GameMapImpl {
        DemoGameMap(GameState& game);
    };
}  // namespace DnD
