cmake_minimum_required(VERSION 3.24)
project(dnd-logic VERSION 1.0)

set(SOURCES "src/GameEntity.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests)
