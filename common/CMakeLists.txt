cmake_minimum_required(VERSION 3.24)
project(dnd-common VERSION 1.0)

add_subdirectory(net)
add_subdirectory(logic)

set(COMMON_LIBRARIES dnd-net dnd-logic)
