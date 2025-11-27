cmake_minimum_required(VERSION 3.15)
project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS)

find_package(CURL REQUIRED)

add_library(utils OBJECT
    src/inputs.cpp
    src/params.cpp
)
add_library(solutions OBJECT
    src/solutions/solutions.cpp
    src/solutions/solution1501.cpp
)

add_executable(aoc src/aoc.cpp)
target_link_libraries(aoc utils solutions CURL::libcurl)
