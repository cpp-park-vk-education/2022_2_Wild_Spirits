cmake_minimum_required(VERSION 3.24)
project(logic-test VERSION 1.0)

enable_testing()

add_executable(${PROJECT_NAME} logic-test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main GTest::gmock_main dnd-logic)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
