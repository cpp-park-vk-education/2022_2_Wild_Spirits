#include "LayerLocation.h"

#include <imgui.h>

#include "LayerMainMenu.h"
#include <Core/Application.h>
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
            if (m_BtnCancel->isHovered()) {
                clearActions();
                m_Field->clearFocused();
                LOGI("Cancel");
                return false;
            }
            if (m_BtnTurn->isHovered()) {
                LOGI("SEND MESSAGE TO SERVER");
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
#ifdef BUILD_LOGIC
        if (Application::get()->getClientSideProcessor()->checkUnappliedChanges()) {
            load();
        }
#endif
    }

    void LayerLocation::renderImGui() {
#ifdef BUILD_LOGIC
        if (m_IsUserCreator && Application::get()->getClientSideProcessor()->checkUnappliedChangesOfDM()) {
            if (ImGui::Begin("New Changes")) {
                auto& changes = Application::get()->getClientSideProcessor()->getChangesDM();
                for (auto& change : changes) {
                    ImGui::DragScalar(change.name.data(), ImGuiDataType_U64, &change.value);
                }
            }
            ImGui::End();
        }

#else
        if (m_IsUserCreator && ImGui::Begin("New Changes")) {
            static size_t testScalar = 0;
            ImGui::DragScalar("changename", ImGuiDataType_U64, &testScalar);
        }
        ImGui::End();

        m_Field->drawAdditionalImGuiWidgets();
        drawCurrentPlayerInfo();
#endif
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

#ifdef BUILD_LOGIC
    void LayerLocation::tryLoadImage(size_t id) {
        if (!m_TextureManager->has(id)) {
            std::shared_ptr<std::string> imgSource = std::make_shared<std::string>();
            if (Application::get()->getClientSideProcessor()->getImage(id, imgSource)) {
                m_TextureManager->add(id, CreateRef<Texture2D>(FromSource { *imgSource }));
            }
        }
    }

    template <typename T>
    void LayerLocation::loadActivatable(T storage) {
        for (auto& item : storage) {
            tryLoadImage(item->getImageId());
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { m_TextureManager->get(item->getImageId()) }, item));
        }
    }

    void LayerLocation::load() {
        // clearScenes();

        m_BottomActions = CreateRef<RenderableBottomActionGroup>(s_BottomActionSpace);
        Ref<DnD::PlayerCharacter> player = Application::get()->getClientSideProcessor()->getCurrentPlayer();
        loadActivatable(player->weapons());
        loadActivatable(player->spells());
        loadActivatable(player->skills());
        loadActivatable(player->consumables());
        addToGui(m_BottomActions);

        Ref<DnD::GameMap> gameMap = Application::get()->getGameMap();

        DnD::Loation& location = gameMap->currentLocation();
        glm::uvec2 fieldSize = glm::uvec2(location.width(), location.height());
        m_Field = CreateRef<RenderableTileGroup>(m_TileTexture, fieldSize);
        addToScene(m_Field);

        auto& npcs = location.npc();
        for (auto& npc : npcs) {
            tryLoadImage(npc->getImageId());
            Ref<RenderableCharacter> renderable =
                CreateRef<RenderableCharacter>(m_TextureManager->get(npc->getImageId()), Color(),
                                               glm::uvec2(npc->centerPos().x, npc->centerPos().y));
            m_Field->addCharacter(renderable);
        }
        auto& characters = gameMap->players();
        for (auto& character : characters) {
            tryLoadImage(character->getImageId());
            Ref<RenderableCharacter> renderable =
                CreateRef<RenderableCharacter>(m_TextureManager->get(character->getImageId()), Color(),
                                               glm::uvec2(character.posX(), character.posY()));
            m_Field->addCharacter(renderable);
        }
    }
#else
    void LayerLocation::load() {
        // clearScenes();

        m_Weapons.push_back(DnD::Weapon(0, DnD::ActivatableInterface::Cast::Tile));
        m_Weapons.push_back(DnD::Weapon(1, DnD::ActivatableInterface::Cast::Tile));
        m_Spells.push_back(DnD::Spell(0, DnD::ActivatableInterface::Cast::Tile));
        m_Spells.push_back(DnD::Spell(1, DnD::ActivatableInterface::Cast::Tile));
        m_Skills.push_back(DnD::Skill(0, DnD::ActivatableInterface::Cast::Tile));
        m_Skills.push_back(DnD::Skill(1, DnD::ActivatableInterface::Cast::Tile));
        m_Consumables.push_back(DnD::Consumable(0, DnD::ActivatableInterface::Cast::Tile));
        m_Consumables.push_back(DnD::Consumable(1, DnD::ActivatableInterface::Cast::Self));

        Ref<Texture2D> textureWeapon =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Skill1.png" });
        Ref<Texture2D> textureSpell =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Skill2.png" });
        Ref<Texture2D> textureSkill =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Skill3.png" });
        Ref<Texture2D> textureConsum =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Skill4.png" });

        m_BottomActions = CreateRef<RenderableBottomActionGroup>(s_BottomActionSpace);
        for (auto& item : m_Weapons) {
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { textureWeapon, glm::vec2(48.0f, 48.0f) }, item));
        }
        for (auto& item : m_Spells) {
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { textureSpell, glm::vec2(48.0f, 48.0f) }, item));
        }
        for (auto& item : m_Skills) {
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { textureSkill, glm::vec2(48.0f, 48.0f) }, item));
        }
        for (auto& item : m_Consumables) {
            m_BottomActions->add(CreateRef<RenderableBottomAction>(
                RenderableTextureProps { textureConsum, glm::vec2(48.0f, 48.0f) }, item));
        }
        addToGui(m_BottomActions);

        glm::uvec2 fieldSize = glm::uvec2(16, 16);
        m_Field = CreateRef<RenderableTileGroup>(m_TileTexture, fieldSize);
        addToScene(m_Field);

        Ref<Texture2D> texturePlayer =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Character.png" });
        Ref<Texture2D> textureEnemy =
            CreateRef<Texture2D>(FromFile { std::string(RES_FOLDER) + "Textures/Location/Enemy.png" });
        for (uint32_t i = 0, j = 2; i < fieldSize.x && j < fieldSize.y; i += 4, j += 2) {
            Ref<RenderableCharacter> character = CreateRef<RenderableCharacter>(
                texturePlayer,
                Color(static_cast<float>(i) / fieldSize.x, 0.0f, static_cast<float>(j) / fieldSize.y, 1.0f),
                glm::uvec2(i, j));
            m_Field->addCharacter(character);
        }
        for (uint32_t i = 1, j = 5; i < fieldSize.x && j < fieldSize.y; i += 3, j += 3) {
            Ref<RenderableCharacter> character = CreateRef<RenderableCharacter>(
                textureEnemy,
                Color(static_cast<float>(i) / fieldSize.x, 0.0f, static_cast<float>(j) / fieldSize.y, 1.0f),
                glm::uvec2(i, j));
            m_Field->addCharacter(character);
        }
    }
#endif

    void LayerLocation::drawCurrentPlayerInfo() {
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
                                       ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav |
                                       ImGuiWindowFlags_NoMove;
        const float PAD = 10.0f;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 workPos = viewport->WorkPos;    // Use work area to avoid menu-bar/task-bar, if any!
        ImVec2 windowPos;
        ImVec2 windowPosPivot { 0.0f, 1.0f };
        ImVec2 workSize = viewport->WorkSize;
        windowPos.x = workPos.x + PAD;
        windowPos.y = workPos.y + workSize.y - PAD;
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowBgAlpha(0.35f);    // Transparent background
        if (ImGui::Begin("My stats", nullptr, windowFlags)) {
            ImGui::Text("HP %u", 100u);
            ImGui::Text("MP %u", 20u);
        }
        ImGui::End();
    }

}    // namespace LM
