cmake_minimum_required(VERSION 3.24)
project(dnd-net VERSION 1.0)

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp" "src/*.h" "src/**/*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)