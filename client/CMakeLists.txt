cmake_minimum_required(VERSION 3.24)
project(Client VERSION 1.0)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    message(STATUS ${CMAKE_CXX_FLAGS})
endif()

add_subdirectory(app)
add_subdirectory(engine)
add_subdirectory(requestor)

add_custom_target(client_check chmod 777 ${CMAKE_SOURCE_DIR}/client_lint.sh && ${CMAKE_SOURCE_DIR}/client_lint.sh)
