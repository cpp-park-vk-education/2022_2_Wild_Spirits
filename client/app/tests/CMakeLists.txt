cmake_minimum_required(VERSION 3.24)
project(ClientAppTests VERSION 1.0)

set(SOURCES tests.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)
target_link_libraries(${PROJECT_NAME} MathLib)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/App")
endif()
