cmake_minimum_required(VERSION 3.24)
project(dnd-gateway VERSION 1.0)

set(SOURCES src/user/UserConnectionImpl.cpp
            src/user/Authorizer.cpp
            src/user/Acceptor.cpp
            src/user/User.cpp
            src/room/RoomImpl.cpp
            src/room/RoomConnector.cpp)

add_subdirectory(tests)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src
                                                  ${PROJECT_SOURCE_DIR}/src/user
                                                  ${PROJECT_SOURCE_DIR}/src/room
                                                  ${PROJECT_SOURCE_DIR}/src/managers)

target_link_libraries(${PROJECT_NAME} PRIVATE dnd-net)
target_link_libraries(${PROJECT_NAME} PRIVATE dnd-db)
target_link_libraries(${PROJECT_NAME} PRIVATE dnd-room)
