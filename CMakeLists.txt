cmake_minimum_required(VERSION 2.8)
project(stdhash)
add_definitions(-Wall)

set(SRC hash.cpp)
add_executable(hash ${SRC})
