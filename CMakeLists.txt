cmake_minimum_required(VERSION 3.30)

project(one_day_one_pattern LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(creational_patterns)
add_subdirectory(beahavioral_patterns)