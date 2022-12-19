#pragma once

#include "Base.h"
#include "Window.h"
#include <Events/EventQueue.h>
#include <ImGui/ImGuiController.h>
#include <Layers/LayerStack.h>

#ifdef BUILD_LOGIC
    #include <ClientRequestProcessor.hpp>
    #include <GameMap.hpp>
    #include <GameState.hpp>
    #include <TurnOrder.hpp>
#endif

namespace LM {

    class Application {
    public:
        Application();

        void run();

        static Application* get() { return s_Instance; }

        Ref<Window> getWindow() { return m_Window; }

#ifdef BUILD_LOGIC
        Ref<ClientSideProcessor> getClientSideProcessor() { return m_ClientSideProcessor; }
        Ref<DnD::GameState> getGameState() { return m_GameState; }
        Ref<DnD::GameMap> getGameMap() { return m_GameMap; }
        Ref<DnD::TurnOrder> getTurnOrder() { return m_TurnOrder; }
#endif

        void addLayer(Ref<Layer> layer) { m_LayerStack->pushLayer(layer); }
        void removeLayer(Layer* layer) { m_LayerStack->popLayer(layer); }

    private:
        void init();
        void onEvent(Ref<Event> event);

    private:
        static inline Application* s_Instance;

    private:
        Ref<Window> m_Window;
        Ref<LayerStack> m_LayerStack;
        Ref<EventQueue> m_EventQueue;
        Ref<ImGuiController> m_ImGuiController;

        bool m_IsRun = true;

#ifdef BUILD_LOGIC
        Ref<DnD::GameState> m_GameState;
        Ref<DnD::GameMap> m_GameMap;
        Ref<DnD::TurnOrder> m_TurnOrder;
        Ref<ClientSideProcessor> m_ClientSideProcessor;
#endif
    };

}    // namespace LM
