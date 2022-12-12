#include "ImGuiController.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Core/Application.h>

namespace LM {

    ImGuiController::ImGuiController() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); //(void)io;
        //io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        //io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImFontConfig fontStyle;
        fontStyle.SizePixels = 24;
        auto font = io.Fonts->AddFontDefault(&fontStyle);
        (void)font;
        IM_ASSERT(font != NULL);

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::get()->getWindow()->getNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    ImGuiController::~ImGuiController() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    void ImGuiController::begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiController::end() {
        ImGuiIO& io = ImGui::GetIO(); //(void)io;
        io.DisplaySize = ImVec2((float)Application::get()->getWindow()->getWidth(), (float)Application::get()->getWindow()->getHeight());

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

}