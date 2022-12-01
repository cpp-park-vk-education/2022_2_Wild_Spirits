cmake_minimum_required(VERSION 3.24)
project(logic-test VERSION 1.0)

enable_testing()

add_executable(${PROJECT_NAME}
    src/area-tests.cpp
    src/effects-tests.cpp
    src/single-tests.cpp
    src/action-tests.cpp
    src/turn-order-tests.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main GTest::gmock_main dnd-logic)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
