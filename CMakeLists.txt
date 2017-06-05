cmake_minimum_required(VERSION 2.8)
project(stdhash)
add_definitions(-Wall)
add_definitions(-DWORDS_LIMIT=5000000)

add_executable(hash hash.cpp)
add_executable(benchmark-ordered benchmark-ordered.cpp)
add_executable(benchmark-unordered benchmark-unordered.cpp)
