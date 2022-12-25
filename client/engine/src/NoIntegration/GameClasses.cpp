#include "GameClasses.hpp"

#include <iostream>

namespace DnD {

    void TestImages::init() {
        srand(time(NULL));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill1.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill2.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill3.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill4.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill5.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill6.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill7.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill8.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill9.png"));
        m_BottomImages.push_back(loadImage("Textures/Location/Skill10.png"));
        m_PlayerImages.push_back(loadImage("Textures/Location/Character1.png"));
        m_PlayerImages.push_back(loadImage("Textures/Location/Character2.png"));
        m_PlayerImages.push_back(loadImage("Textures/Location/Character3.png"));
        m_PlayerImages.push_back(loadImage("Textures/Location/Character4.png"));
        m_EnemyImages.push_back(loadImage("Textures/Location/Enemy1.png"));
        m_EnemyImages.push_back(loadImage("Textures/Location/Enemy2.png"));
        m_EnemyImages.push_back(loadImage("Textures/Location/Enemy3.png"));
        m_EnemyImages.push_back(loadImage("Textures/Location/Enemy4.png"));
        m_EnemyImages.push_back(loadImage("Textures/Location/Enemy5.png"));
        std::cout << "Test textures count: "
                  << m_BottomImages.size() + m_PlayerImages.size() + m_EnemyImages.size() +
                         m_UserImages.size()
                  << std::endl;
    }

    size_t TestImages::addImage(const std::string& source) {
        size_t id =
            m_BottomImages.size() + m_PlayerImages.size() + m_EnemyImages.size() + m_UserImages.size();

        m_UserImages.emplace_back(source);
        return id;
    }

    std::string TestImages::loadImage(const std::string& path) {
        std::ifstream input(std::string(RES_FOLDER) + path, std::ios::binary);
        return std::string(std::istreambuf_iterator<char>(input), {});
    }

    std::string TestImages::getSourceById(size_t id) {
        if (id < m_BottomImages.size()) {
            return m_BottomImages[id];
        }
        if (id < m_BottomImages.size() + m_PlayerImages.size()) {
            return m_PlayerImages[id - m_BottomImages.size()];
        }
        if (id < m_BottomImages.size() + m_PlayerImages.size() + m_EnemyImages.size()) {
            return m_EnemyImages[id - m_BottomImages.size() - m_PlayerImages.size()];
        }

        return m_UserImages[id - m_BottomImages.size() - m_PlayerImages.size() - m_EnemyImages.size()];
    }

}    // namespace DnD
