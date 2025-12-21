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
target_link_libraries(utils PUBLIC OpenSSL::Crypto CURL::libcurl)

add_library(solutions OBJECT
    src/solutions/solutions.cpp
    src/solutions/2015/01/solution1501.cpp
    src/solutions/2015/02/solution1502.cpp
    src/solutions/2015/03/solution1503.cpp
    src/solutions/2015/04/solution1504.cpp
    src/solutions/2015/05/solution1505.cpp
    src/solutions/2015/06/solution1506.cpp
    src/solutions/2015/07/solution1507.cpp
)
target_include_directories(solutions PRIVATE src/solutions)
target_link_libraries(solutions PUBLIC OpenSSL::Crypto CURL::libcurl)

add_executable(unit-tests
    src/solutions/2015/02/tests.cpp
    src/solutions/2015/03/tests.cpp
    src/solutions/2015/04/tests.cpp
    src/solutions/2015/05/tests.cpp
    src/solutions/2015/06/tests.cpp
    src/solutions/2015/07/tests.cpp
)
target_include_directories(unit-tests PRIVATE src/solutions)
target_link_libraries(
    unit-tests
    PRIVATE
    solutions
    OpenSSL::Crypto GTest::gtest_main
)

enable_testing()
add_test(unit-tests unit-tests)

add_executable(aoc src/aoc.cpp)
target_link_libraries(
    aoc
    PRIVATE
    utils solutions
    OpenSSL::Crypto CURL::libcurl
)
