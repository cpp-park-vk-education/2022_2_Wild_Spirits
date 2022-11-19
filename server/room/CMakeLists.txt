cmake_minimum_required(VERSION 3.24)
project(dnd-room VERSION 1.0)

add_subdirectory(tests)

set(SOURCES "src/main.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
