#include "ImGuiFuncs.h"

namespace LM {

    constexpr float PAD = 10.0f;

    ImGuiWindowFlags ImGuiFuncs::SetNextWindowCenterAutoResize() {
        const ImGuiIO& io = ImGui::GetIO();
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always,
                                ImVec2(0.5f, 0.5f));
        return ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
    }

    ImGuiWindowFlags ImGuiFuncs::SetNextWindowOverlayBottomLeft() {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 workPos = viewport->WorkPos;
        ImVec2 windowPos;
        ImVec2 windowPosPivot { 0.0f, 1.0f };
        ImVec2 workSize = viewport->WorkSize;
        windowPos.x = workPos.x + PAD;
        windowPos.y = workPos.y + workSize.y - PAD;
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowBgAlpha(0.35f);
        return ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
               ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
               ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
    }

}    // namespace LM
