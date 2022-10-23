cmake_minimum_required(VERSION 3.24)
project(ClientEngineTests VERSION 1.0)

enable_testing()

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/Engine/Tests")
endif()