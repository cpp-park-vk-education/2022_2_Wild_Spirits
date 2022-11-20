cmake_minimum_required(VERSION 3.24)
project(dnd-logic VERSION 1.0)

set(SOURCES "src/GameEntity.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include/activatable
    ${PROJECT_SOURCE_DIR}/include/base
    ${PROJECT_SOURCE_DIR}/include/character
    ${PROJECT_SOURCE_DIR}/include/items)

add_subdirectory(tests)
