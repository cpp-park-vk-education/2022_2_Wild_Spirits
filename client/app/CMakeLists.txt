cmake_minimum_required(VERSION 3.24)
project(ClientApp VERSION 1.0)

set(SOURCES 
    src/main.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME} PRIVATE ClientEngine)

add_subdirectory(vendor/mathlib)
add_subdirectory(tests)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/App")
endif()
