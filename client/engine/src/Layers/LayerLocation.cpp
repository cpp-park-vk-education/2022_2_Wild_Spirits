#include "LayerLocation.h"

#include <imgui.h>

#include "LayerMainMenu.h"
#include <Core/Application.h>
#include <ImGui/ImGuiFuncs.h>
#include <Utils/ConsoleLog.h>

namespace LM {

    LayerLocation::LayerLocation(bool isUserCreator) : m_IsUserCreator(isUserCreator) {
        init();

        load();
    }

    LayerLocation::~LayerLocation() { }

    void LayerLocation::onEvent(Ref<Event> event) {
        Layer::onEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyPressedEvent>([&](Ref<KeyPressedEvent> event) {
            if (event->getKeyCode() == Key::Escape) {
                Application::get()->addLayer(CreateRef<LayerMainMenu>());
                Application::get()->removeLayer(this);
                return false;
            }
            return false;
        });
        dispatcher.dispatch<MouseButtonPressedEvent>([&](Ref<MouseButtonPressedEvent> event) {
            const ImGuiIO& io = ImGui::GetIO();
            LOGI("io.WantCaptureMouse: ", io.WantCaptureMouse);
            if (io.WantCaptureMouse) {
                return false;
            }
            if (m_BtnCancel->isHovered()) {
                clearActions();
                m_Field->clearFocused();
                LOGI("Cancel");
                return false;
            }
            if (m_BtnTurn->isHovered()) {
                LOGI("SEND MESSAGE TO SERVER");
                if (m_ActionMove) {
                    Application::get()->getClientSideProcessor()->sendRequest(*m_ActionMove);
                }
                if (m_ActionUse) {
                    Application::get()->getClientSideProcessor()->sendRequest(*m_ActionUse);
                }

                clearActions();
                m_Field->clearFocused();
                return false;
            }
            if (auto action = m_BottomActions->getAction(); action) {
                clearActions();
                m_Field->clearFocused();
                addToGui(m_BtnCancel);
                m_BottomActions->setFocus();
                m_ActionUse = action;
                LOGI("Use Action Created!");
                return false;
            }
            if (m_Field->hasHovered()) {
                LOGI("Hovered tile: ", m_Field->getHoveredX(), " ", m_Field->getHoveredY());
                m_Field->setHoveredInFocus();
                if (m_ActionUse) {
                    LOGI("UseAction setTarget");
                    if (m_ActionUse->isFirstSet()) {
                        addToGui(m_BtnTurn);
                    }
                    m_ActionUse->setTarget(m_Field->getHoveredX(), m_Field->getHoveredY());
                    return false;
                }
                LOGI("MoveAction setTarget");
                clearActions();
                addToGui(m_BtnCancel);
                addToGui(m_BtnTurn);
                m_ActionMove = CreateRef<MoveAction>(m_Field->getHoveredX(), m_Field->getHoveredY());
                return false;
            }

            return false;
        });
    }

    void LayerLocation::init() {
        Ref<Texture2D> textureCancel =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/BtnCancel.png" });
        Ref<Texture2D> textureTurn =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/BtnTurn.png" });
        m_BtnCancel = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps { textureCancel },
            RenderableGuiProps { { GuiAlign::kEnd }, glm::vec2(-16.0f, 16.0f) });
        m_BtnTurn = CreateRef<RenderableGuiTexture>(
            RenderableTextureProps { textureTurn },
            RenderableGuiProps { { GuiAlign::kEnd }, glm::vec2(-16.0f, 196.0f) });
        m_TextureManager = CreateRef<TextureManager>();
        m_TileTexture =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Tile.png" });
    }

    void LayerLocation::onUpdate(Tick tick) {
        Layer::onUpdate(tick);
        if (Application::get()->getClientSideProcessor()->checkUnappliedChanges()) {
            LOGI("UC");
            load();
            Application::get()->getClientSideProcessor()->setUpToDate();
        }
    }

    void LayerLocation::renderImGui() {
#ifdef BUILD_LOGIC
        // if (m_IsUserCreator && Application::get()->getClientSideProcessor()->checkUnappliedChanges()) {
        //     if (ImGui::Begin("New Changes")) {
        //         auto& changes = Application::get()->getClientSideProcessor()->getChanges();
        //         for (auto& change : changes) {
        //             ImGui::DragScalar(change.name.data(), ImGuiDataType_U64, &change.value);
        //         }
        //     }
        //     ImGui::End();
        // }

#else
        if (m_IsUserCreator && Application::get()->getClientSideProcessor()->checkUnappliedChangesOfDM()) {
            if (ImGui::Begin("New Changes")) {
                auto& changes = Application::get()->getClientSideProcessor()->getChangesDM();
                for (auto& change : changes) {
                    ImGui::DragScalar(change.name.data(), ImGuiDataType_U64, &change.value);
                }
            }
            ImGui::End();
        }
#endif
        if (m_IsUserCreator && ImGui::Begin("New Changes")) {
            static size_t testScalar = 0;
            ImGui::DragScalar("changename", ImGuiDataType_U64, &testScalar);
        }
        ImGui::End();

        m_Field->drawAdditionalImGuiWidgets();
        drawCurrentPlayerInfo();
        drawDebugWindow();
    }

    bool LayerLocation::hasActions() const {
        if (m_ActionMove) {
            return true;
        }
        if (m_ActionUse) {
            return true;
        }

        return false;
    }

    void LayerLocation::clearActions() {
        m_BottomActions->setUnFocus();
        removeFromGui(m_BtnCancel);
        m_BtnCancel->setHovered(false);
        removeFromGui(m_BtnTurn);
        m_BtnTurn->setHovered(false);
        m_ActionMove = Ref<MoveAction>();
        m_ActionUse = Ref<UseAction>();
    }

    void LayerLocation::tryLoadImage(size_t id) {
        if (!m_TextureManager->has(id)) {
            std::shared_ptr<std::string> imgSource = std::make_shared<std::string>();
            if (Application::get()->getClientSideProcessor()->getImage(std::to_string(id), imgSource)) {
                m_TextureManager->add(id, CreateRef<Texture2D>(FromSource { *imgSource }));
            }
        }
    }

    template <typename T>
    void LayerLocation::loadActivatableShared(T storage) {
        LOGI("Started loading activatable");
        for (auto& [id, item] : storage) {
            tryLoadImage(item->getImageId());
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { m_TextureManager->get(item->getImageId()), glm::vec2(48.0f, 48.0f) },
                *item));
        }
        LOGI("finished loading actibatable");
    }

    template <typename T>
    void LayerLocation::loadActivatable(T storage) {
        LOGI("started loading actibatable non shared");
        for (auto& [id, item] : storage) {
            tryLoadImage(item.getImageId());
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { m_TextureManager->get(item.getImageId()), glm::vec2(48.0f, 48.0f) },
                item));
        }
        LOGI("finished loading actibatable non shared");
    }

    void LayerLocation::load() {
        clearScenes();

        LOGI("Layer Location Reload");

        Ref<DnD::GameMap> gameMap = Application::get()->getGameMap();

        m_BottomActions = CreateRef<RenderableBottomActionGroup>(s_BottomActionSpace);
        size_t playerId = Application::get()->getClientSideProcessor()->getPlayerId();
        LOGI(playerId);
        std::shared_ptr<DnD::PlayerCharacter> player = gameMap->players().safeGet(playerId);
        
        loadActivatableShared(player->weapons());
        loadActivatableShared(player->spells());
        loadActivatable(player->skills());
        loadActivatable(player->consumables());
        addToGui(m_BottomActions);

        DnD::Location& location = gameMap->currentLocation();
        glm::uvec2 fieldSize = glm::uvec2(location.width(), location.height());
        m_Field = CreateRef<RenderableTileGroup>(m_TileTexture, fieldSize);
        addToScene(m_Field);

        auto& npcs = location.npc();
        for (auto& [id, npc] : npcs) {
            tryLoadImage(npc->getImageId());
            Ref<RenderableCharacter> renderable = CreateRef<RenderableCharacter>(
                m_TextureManager->get(npc->getImageId()), Color(1.0f, 1.0f, 1.0f, 1.0f),
                glm::uvec2(npc->centerPos().x, npc->centerPos().y));
            m_Field->addCharacter(renderable);
        }
        auto& characters = gameMap->players();
        for (auto& [id, character] : characters) {
            tryLoadImage(character->getImageId());
            Ref<RenderableCharacter> renderable = CreateRef<RenderableCharacter>(
                m_TextureManager->get(character->getImageId()), Color(1.0f, 1.0f, 1.0f, 1.0f),
                glm::uvec2(character->centerPos().x, character->centerPos().y));
            m_Field->addCharacter(renderable);
        }
    }

    void LayerLocation::drawCurrentPlayerInfo() {
        if (ImGui::Begin("My stats", nullptr, ImGuiFuncs::SetNextWindowOverlayBottomLeft())) {
            Ref<DnD::GameMap> gameMap = Application::get()->getGameMap();
            size_t playerId = Application::get()->getClientSideProcessor()->getPlayerId();
            std::shared_ptr<DnD::PlayerCharacter> player = gameMap->players().safeGet(playerId);

            ImGui::Text("HP: %d/%u", player->hp(), player->maxHP());
            ImGui::Text("CP: %u/%u", player->actionPoints(), player->maxActionPoints());
            ImGui::Separator();
            ImGui::Text("Money: %d", player->money());
        }
        ImGui::End();
    }

    void LayerLocation::drawDebugWindow() {
#ifndef BUILD_LOGIC
        if (ImGui::Begin("Location Debug")) {
            ImGui::Text("Current Location: %lu", Application::get()->getGameMap()->currentLocation().id());
            for (auto loc : Application::get()->getGameMap()->locations()) {
                if (ImGui::Button(("Go to Location " + std::to_string(loc.second.id())).data())) {
                    Application::get()->getGameMap()->switchLocation(loc.second.id());
                    Application::get()->getClientSideProcessor()->setUnappliedChanges(true);
                }
            }
        }
        ImGui::End();
#endif
    }

}    // namespace LM
