cmake_minimum_required(VERSION 3.24)
project(dnd-logic VERSION 1.0)

set(SOURCES
     src/Action.cpp
     src/Effect.cpp
     src/GameEntity.cpp
     src/CharacterInstance.cpp
     src/GameMap.cpp
     src/GameState.cpp
     src/Location.cpp
     src/OnLocation.cpp
     src/TurnOrder.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/activatable
    ${PROJECT_SOURCE_DIR}/include/base
    ${PROJECT_SOURCE_DIR}/include/character
    ${PROJECT_SOURCE_DIR}/include/items
    ${PROJECT_SOURCE_DIR}/include/structure)

add_subdirectory(tests)
