cmake_minimum_required(VERSION 3.24)
project(dnd-gateway VERSION 1.0)

set(SOURCES "src/main.cpp")

add_subdirectory(tests)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE dnd-db)
target_link_libraries(${PROJECT_NAME} PRIVATE dnd-room)
