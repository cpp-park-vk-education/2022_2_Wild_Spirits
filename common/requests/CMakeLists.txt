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
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})


target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/interfaces
)




add_subdirectory(tests)