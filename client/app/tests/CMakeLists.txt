cmake_minimum_required(VERSION 3.24)
project(ClientAppTests VERSION 1.0)

enable_testing()

add_executable(${PROJECT_NAME} tests.cpp)

target_link_libraries(${PROJECT_NAME} ${MathLib_LIBRARY_DIRS} GTest::gtest_main GTest::gmock_main)
target_include_directories(${PROJECT_NAME} PRIVATE ${MathLib_INCLUDE_DIRS})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/App/Tests")
endif()
