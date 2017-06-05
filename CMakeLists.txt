cmake_minimum_required(VERSION 2.8)
project(stdhash)
add_definitions(-Wall)
add_definitions(-DWORDS_LIMIT=500000)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/benchmark/include)

add_subdirectory(benchmark)

add_executable(hash hash.cpp)
add_executable(run-benchmark benchmark.cpp)
target_link_libraries(run-benchmark benchmark)