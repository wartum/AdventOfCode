cmake_minimum_required(VERSION 3.15)
project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS)

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

add_library(utils OBJECT
    src/inputs.cpp
    src/params.cpp
)

add_library(solutions OBJECT
    src/solutions/solutions.cpp
    src/solutions/solution1501.cpp
    src/solutions/solution1502.cpp
    src/solutions/solution1503.cpp
    src/solutions/solution1504.cpp
)

add_executable(unit-tests
    src/solutions/solution1502tests.cpp
    src/solutions/solution1503tests.cpp
    src/solutions/solution1504tests.cpp
)
target_link_libraries(unit-tests PRIVATE solutions OpenSSL::Crypto GTest::gtest_main)

enable_testing()
add_test(unit-tests unit-tests)

add_executable(aoc src/aoc.cpp)
target_link_libraries(aoc PRIVATE utils solutions OpenSSL::Crypto CURL::libcurl)
