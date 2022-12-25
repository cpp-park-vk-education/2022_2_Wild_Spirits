#pragma once

#include <imgui.h>

namespace LM {

    class ImGuiFuncs {
    public:
        static ImGuiWindowFlags SetNextWindowCenterAutoResize();
        static ImGuiWindowFlags SetNextWindowOverlayBottomLeft();
    };

}    // namespace LM
