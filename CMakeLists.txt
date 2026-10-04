cmake_minimum_required(VERSION 3.29)

project(benchmark)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BENCHMARK_ENABLE_DOXYGEN OFF)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE benchmark::benchmark)
