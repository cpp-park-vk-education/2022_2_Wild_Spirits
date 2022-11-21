#pragma once

#include <cstdint>

namespace LM {

    struct RenderableGuiAlight {
        enum class Align : uint8_t
        {
            kStart = 0,
            kCenter,
            kEnd,
        };

        Align vertical = Align::kStart;
        Align horizontal = Align::kStart;
    };

}
