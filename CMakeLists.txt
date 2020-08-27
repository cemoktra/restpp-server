cmake_minimum_required(VERSION 3.16)

project("Rest++")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(submodules)

add_subdirectory(benchmarks)

add_subdirectory(server)
add_subdirectory(example)