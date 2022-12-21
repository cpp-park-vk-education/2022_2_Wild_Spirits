cmake_minimum_required(VERSION 3.24)

project(request-processor VERSION 1.0)


set(SOURCES
        src/ActionHandler.cpp
        src/ChangeGetter.cpp
    src/ClientProcessorEngine.cpp
    src/ClientRequestProcessor.cpp
    src/GameStateChanger.cpp
    src/RequestStringGenerator.cpp
    src/RoomProcessorEngine.cpp
    src/RoomRequestProcessor.cpp
    src/StringRequestParser.cpp
        .
)

find_package(nlohmann_json 3.11.1 REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} GTest::gmock_main nlohmann_json::nlohmann_json
        dnd-logic ClientRequestor)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/common/requests/include
    ${PROJECT_SOURCE_DIR}/interfaces
    ${PROJECT_SOURCE_DIR}/../client/requestor/Actions
        ${PROJECT_SOURCE_DIR}/logic/activatable
)




add_subdirectory(tests)
