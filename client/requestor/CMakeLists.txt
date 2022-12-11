cmake_minimum_required(VERSION 3.24)
project(ClientRequestor VERSION 1.0)

set(SOURCES 
    Actions/Action.h
    Actions/UseActions.cpp Actions/UseActions.h
    Actions/MoveAction.cpp Actions/MoveAction.h
    
    Classes/Room.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

if (${BUILD_LOGIC})
    add_definitions(-DBUILD_LOGIC)
endif()

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/Engine/deps")
endif()
