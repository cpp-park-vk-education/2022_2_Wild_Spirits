#pragma once

#include <cstdint>

namespace LM {

    enum class GuiAlign: uint8_t
    {
        kStart = 0,
        kCenter,
        kEnd,
    };


    struct RenderableGuiAlign {
        GuiAlign horizontal = GuiAlign::kStart;
        GuiAlign vertical = GuiAlign::kStart;
    };

}    // namespace LM
