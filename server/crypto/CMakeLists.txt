cmake_minimum_required(VERSION 3.24)
project(dnd-crypto VERSION 1.0)

set(SOURCES src/crypto_impl.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
