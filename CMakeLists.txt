cmake_minimum_required(VERSION 3.10.2)
project(HybridSort VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# project options
option(BUILD_TESTING "Build the tests"  ON)
option(BUILD_BENCHMARK "Build the benchmarks"  OFF)

if (BUILD_TESTING)
    add_subdirectory(test)
endif()

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()
