cmake_minimum_required(VERSION 3.24)

project(request-processor VERSION 1.0)


set(SOURCES
    src/ActionCollector.cpp
    src/ActionHandler.cpp
    src/ChangeCollector.cpp
    src/ChangeGetter.cpp
    src/ClientProcessorEngine.cpp
    src/ClientRequestProcessor.cpp
    src/GameStateChanger.cpp
    src/RequestStringGenerator.cpp
    src/RoomProcessorEngine.cpp
    src/RoomRequestProcessor.cpp
    src/StringRequestParser.cpp
        ../../client/requestor/Actions/MoveAction.cpp
        ../../client/requestor/Actions/UseActions.cpp
    ../../client/requestor/Actions/Actions.h
)

find_package(nlohmann_json 3.11.1 REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::gmock_main nlohmann_json::nlohmann_json
        dnd-logic)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/common/requests/include
    ${PROJECT_SOURCE_DIR}/interfaces
    ${PROJECT_SOURCE_DIR}/../client/requestor/Actions
)




add_subdirectory(tests)