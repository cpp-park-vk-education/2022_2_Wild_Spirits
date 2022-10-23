cmake_minimum_required(VERSION 3.24)
project(ClientApp VERSION 1.0)

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp" "src/*.h" "src/**/*.h")
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(vendor/mathlib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${MathLib_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME} PRIVATE ClientEngine)


if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/App")
endif()

add_subdirectory(tests)
