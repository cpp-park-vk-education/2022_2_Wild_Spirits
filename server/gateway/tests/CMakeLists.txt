cmake_minimum_required(VERSION 3.24)
project(gateway-test VERSION 1.0)

enable_testing()

add_executable(${PROJECT_NAME} gateway-test.cpp)

target_link_libraries(${PROJECT_NAME} GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
