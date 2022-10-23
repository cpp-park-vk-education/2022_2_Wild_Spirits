cmake_minimum_required(VERSION 3.24)
project(MathLib VERSION 1.0)

file(GLOB SOURCES "*.cpp" "**/*.cpp" "*.h" "**/*.h")
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATH_LIB_INCLUDE_DIRS})

set(MathLib_LIBRARY_DIRS ${PROJECT_NAME} PARENT_SCOPE)
set(MathLib_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/App/vendor")
endif()