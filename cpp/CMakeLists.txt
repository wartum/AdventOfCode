cmake_minimum_required(VERSION 3.15)
project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)

add_library(utils OBJECT src/inputs.cpp src/params.cpp)

add_executable(aoc src/aoc.cpp)

target_link_libraries(aoc utils CURL::libcurl)
