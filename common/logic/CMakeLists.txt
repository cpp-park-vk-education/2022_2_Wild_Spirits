cmake_minimum_required(VERSION 3.24)
project(dnd-logic VERSION 1.0)

set(SOURCES
     src/activatable/Action.cpp
     src/activatable/Activatable.cpp
     src/activatable/Effect.cpp
     src/base/Dice.cpp
     src/base/GameEntity.cpp
     src/items/Armor.cpp
     src/items/Item.cpp
     src/items/Spell.cpp
     src/items/Skill.cpp
     src/character/OnLocation.cpp
     src/character/Character.cpp
     src/character/CharacterInstance.cpp
     src/character/PlayerCharacter.cpp
     src/character/NPC_Instance.cpp
     src/structure/Location.cpp
     src/structure/GameState.cpp
     src/structure/GameMap.cpp
     src/structure/DamageTypeStorage.cpp
     src/structure/TurnOrder.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/activatable
    ${PROJECT_SOURCE_DIR}/include/base
    ${PROJECT_SOURCE_DIR}/include/character
    ${PROJECT_SOURCE_DIR}/include/items
    ${PROJECT_SOURCE_DIR}/include/structure)

add_subdirectory(tests)
