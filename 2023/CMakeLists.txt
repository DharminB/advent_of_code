cmake_minimum_required(VERSION 3.10)
project(aoc_2023)

add_compile_options(-std=c++11 -Wall)

include_directories(
    src
)

add_executable(aoc_2023
    src/main.cpp
)
target_link_libraries(aoc_2023
)
