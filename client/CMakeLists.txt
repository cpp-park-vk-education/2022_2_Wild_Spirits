cmake_minimum_required(VERSION 3.24)
project(Client VERSION 1.0)

option(BUILD_LOGIC "GLFW_BUILD_DOCS" ON)

add_subdirectory(app)
add_subdirectory(engine)
add_subdirectory(requestor)

add_custom_target(client_check chmod 777 ${CMAKE_SOURCE_DIR}/client_lint.sh && ${CMAKE_SOURCE_DIR}/client_lint.sh)
