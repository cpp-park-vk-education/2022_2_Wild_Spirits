#pragma once

#include <cstdint>
#include <ctime>
#include <fstream>
#include <map>
#include <memory>
#include <random>

#include <glm/glm.hpp>

#include <Actions/UseActions.h>

namespace DnD {

    class TestImages {
    public:
        static void init();
        static size_t getRandomBottomId() { return rand() % m_BottomImages.size(); }
        static size_t getRandomPlayerId() { return m_BottomImages.size() + rand() % m_PlayerImages.size(); }
        static size_t getRandomEnemyId() {
            return m_BottomImages.size() + m_PlayerImages.size() + rand() % m_EnemyImages.size();
        }

        static size_t addImage(const std::string& source);

        static std::string getSourceById(size_t id);

    protected:
        static std::string loadImage(const std::string& path);

    protected:
        static inline std::vector<std::string> m_BottomImages;
        static inline std::vector<std::string> m_PlayerImages;
        static inline std::vector<std::string> m_EnemyImages;
        static inline std::vector<std::string> m_UserImages;
    };

    template <typename T>
    class Storage {
    protected:
        std::map<size_t, T> data;

    public:
        using iterator = typename decltype(data)::iterator;
        using const_iterator = typename decltype(data)::const_iterator;

        iterator begin() { return data.begin(); }
        iterator end() { return data.end(); }

        const_iterator begin() const { return data.cbegin(); }
        const_iterator end() const { return data.cend(); }

        void add(size_t id, const T& val) { data.emplace(id, val); }

        T safeGet(size_t id) { return data[id]; }
        T& get(size_t id) {
            auto it = data.find(id);
            return it->second;
        }
    };

    template <typename T>
    class SharedStorage : public Storage<std::shared_ptr<T>> {
    public:
    private:
    };

    class CharacterInstance : public ImageGetter {
    public:
        CharacterInstance(size_t posX, size_t posY, size_t imageId)
            : ImageGetter(imageId),
              m_PosX(posX),
              m_PosY(posY) { }

        glm::uvec2 centerPos() const { return glm::uvec2(m_PosX, m_PosY); }

        void setPosX(long long x) { m_PosX = x; }
        void setPosY(long long y) { m_PosY = y; }

        int hp() const { return m_HP; }
        unsigned int maxHP() const { return m_MaxHP; }
        void takeDamage(unsigned int damage) { m_HP -= damage; }

        int money() const { return 9998; }

        unsigned int actionPoints() const { return 9; }
        unsigned int maxActionPoints() const { return 10; }

    protected:
        size_t m_PosX;
        size_t m_PosY;
        int m_HP = 100;
        unsigned int m_MaxHP = 100;
    };

    class PlayerCharacter : public CharacterInstance {
    public:
        PlayerCharacter(size_t posX, size_t posY, size_t imageId) : CharacterInstance(posX, posY, imageId) {
            m_Weapons.add(0, std::make_shared<Weapon>(0, ActivatableInterface::Cast::Tile,
                                                      TestImages::getRandomBottomId()));
            m_Weapons.add(1, std::make_shared<Weapon>(1, ActivatableInterface::Cast::Tile,
                                                      TestImages::getRandomBottomId()));
            m_Spells.add(0, std::make_shared<Spell>(0, ActivatableInterface::Cast::Tile,
                                                    TestImages::getRandomBottomId()));
            m_Spells.add(1, std::make_shared<Spell>(1, ActivatableInterface::Cast::Tile,
                                                    TestImages::getRandomBottomId()));
            m_Skills.add(
                0, Skill_Instance(0, ActivatableInterface::Cast::Tile, TestImages::getRandomBottomId()));
            m_Skills.add(
                1, Skill_Instance(1, ActivatableInterface::Cast::Tile, TestImages::getRandomBottomId()));
            m_Consumables.add(
                0, Consumable(0, ActivatableInterface::Cast::Tile, TestImages::getRandomBottomId()));
            m_Consumables.add(
                1, Consumable(1, ActivatableInterface::Cast::Self, TestImages::getRandomBottomId()));
        }

        SharedStorage<Weapon> weapons() { return m_Weapons; }
        SharedStorage<Spell> spells() { return m_Spells; }
        Storage<Skill_Instance> skills() { return m_Skills; }
        Storage<Consumable> consumables() { return m_Consumables; }

    protected:
        SharedStorage<Weapon> m_Weapons;
        SharedStorage<Spell> m_Spells;
        Storage<Skill_Instance> m_Skills;
        Storage<Consumable> m_Consumables;
    };

    class NPC_Instance : public CharacterInstance {
    public:
        NPC_Instance(size_t posX, size_t posY, size_t imageId) : CharacterInstance(posX, posY, imageId) { }

    protected:
    };

    class Location {
    public:
        Location(size_t id, size_t width, size_t height) : m_Id(id), m_Widht(width), m_Height(height) {
            m_NPC.add(0, std::make_shared<NPC_Instance>(5, 5, TestImages::getRandomEnemyId()));
            m_NPC.add(1, std::make_shared<NPC_Instance>(7, 7, TestImages::getRandomEnemyId()));
            m_NPC.add(2, std::make_shared<NPC_Instance>(3, 7, TestImages::getRandomEnemyId()));
            m_NPC.add(3, std::make_shared<NPC_Instance>(7, 2, TestImages::getRandomEnemyId()));
        }

        size_t id() const { return m_Id; }
        size_t width() const { return m_Widht; }
        size_t height() const { return m_Height; }
        SharedStorage<NPC_Instance>& npc() { return m_NPC; }

    protected:
        size_t m_Id;
        size_t m_Widht;
        size_t m_Height;
        SharedStorage<NPC_Instance> m_NPC;
    };

}    // namespace DnD
