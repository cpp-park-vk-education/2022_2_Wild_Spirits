cmake_minimum_required(VERSION 3.24)
project(dnd VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_CLIENT "Build Client" ON)
option(BUILD_SERVER "Build Server" ON)

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

if (${BUILD_SERVER})
    FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx
        GIT_TAG 7.7.4
        FIND_PACKAGE_ARGS NAMES libpqxx
    )

    option(BUILD_TEST OFF)
    FetchContent_MakeAvailable(libpqxx)
endif()

# <BOOST>

find_package(Boost 1.80.0) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

# </BOOST>
    
set(SANITIZER_FLAGS "-fsanitize=leak,undefined,address")
set(ERROR_FLAGS "-Wall")
if(MSVC)
	set(ERROR_FLAGS "${ERROR_FLAGS} -W4")
else()
	set(ERROR_FLAGS "${ERROR_FLAGS} -Wpedantic -Werror")
endif()

option(SANITIZE "Enable sanitizers" ON)
if (${SANITIZE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
endif()

option(DEBUG "Enable debug" ON)
if (${DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ERROR_FLAGS}")

add_custom_target(check chmod 777 ${CMAKE_SOURCE_DIR}/lint.sh && ${CMAKE_SOURCE_DIR}/lint.sh)

add_subdirectory(common)

if (${BUILD_SERVER})
    add_subdirectory(server)
endif()

if (${BUILD_CLIENT})
    add_subdirectory(client)
endif()
