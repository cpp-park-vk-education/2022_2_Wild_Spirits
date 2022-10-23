cmake_minimum_required(VERSION 3.24)
project(ClientEngine VERSION 1.0)

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp" "src/*.h" "src/**/*.h")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

#add_subdirectory(vendor/glfw)
#target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
#target_include_directories(${PROJECT_NAME} PRIVATE glfw_INCLUDE_DIRS)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Client/Engine")
endif()

add_subdirectory(test)