cmake_minimum_required(VERSION 3.24)
project(dnd VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
    FIND_PACKAGE_ARGS NAMES GTest
)

FetchContent_MakeAvailable(googletest)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
set_target_properties(gmock gmock_main gtest gtest_main PROPERTIES FOLDER "GTest")
endif()

FetchContent_Declare(
    libpqxx
    GIT_REPOSITORY https://github.com/jtv/libpqxx
    GIT_TAG 7.7.4
    FIND_PACKAGE_ARGS NAMES libpqxx
)

option(BUILD_TEST OFF)
FetchContent_MakeAvailable(libpqxx)

set(SANITIZER_FLAGS "-fsanitize=leak,undefined,address")
set(ERROR_FLAGS "-Wall -Wpedantic -Werror")

option(SANITIZE ON)
if (${SANITIZE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
endif()

option(DEBUG ON)
if (${DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ERROR_FLAGS}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_custom_target(check ${CMAKE_SOURCE_DIR}/lint.sh)

add_subdirectory(common)
add_subdirectory(server)
# add_subdirectory(client)