#pragma once

#include <cstdint>

namespace LM {

    struct RenderableGuiAlign {
        enum class Align : uint8_t
        {
            kStart = 0,
            kCenter,
            kEnd,
        };

        Align horizontal = Align::kStart;
        Align vertical = Align::kStart;
    };

}
