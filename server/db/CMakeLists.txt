cmake_minimum_required(VERSION 3.24)
project(dnd-db VERSION 1.0)

set(SOURCES src/DBQueue.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE pqxx)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
