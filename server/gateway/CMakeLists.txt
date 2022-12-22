cmake_minimum_required(VERSION 3.24)
project(dnd-gateway VERSION 1.0)

set(SOURCES src/user/UserConnectionImpl.cpp
            src/user/Authorizer.cpp
            src/user/Acceptor.cpp
            src/user/User.cpp
            src/room/RoomImpl.cpp
            src/room/RoomConnector.cpp
            src/imageStorage/Image.cpp
            src/imageStorage/ImageStorage.cpp)

add_subdirectory(tests)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src
                                                  ${PROJECT_SOURCE_DIR}/src/user
                                                  ${PROJECT_SOURCE_DIR}/src/room
                                                  ${PROJECT_SOURCE_DIR}/src/managers
                                                  ${PROJECT_SOURCE_DIR}/src/imageStorage)

target_link_libraries(${PROJECT_NAME} PRIVATE dnd-net dnd-db dnd-room)
