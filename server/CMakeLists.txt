cmake_minimum_required(VERSION 3.24)
project(dnd-server VERSION 1.0)

add_subdirectory(db)
add_subdirectory(room)
add_subdirectory(gateway)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE dnd-gateway)

target_link_libraries(${PROJECT_NAME} PRIVATE ${COMMON_LIBRARIES})

add_subdirectory(tests)
