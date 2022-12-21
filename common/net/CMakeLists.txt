cmake_minimum_required(VERSION 3.24)
project(dnd-net VERSION 1.0)

set(SOURCES src/Buffer.cpp
            src/WebSocketStream.cpp
            src/WebSocketConnection.cpp
            src/EventLoop.cpp
            src/ClientConnection.cpp
            src/Encoder.cpp
            )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(tests)
