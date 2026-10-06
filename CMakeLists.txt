cmake_minimum_required(VERSION 3.29)

project(benchmark)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BENCHMARK_ENABLE_DOXYGEN OFF)
set(BENCHMARK_ENABLE_INSTALL OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark EXCLUDE_FROM_ALL)

add_executable(bench32 main.cpp)
target_link_libraries(bench32 PRIVATE benchmark::benchmark)
target_compile_definitions(bench32 PRIVATE BENCH_32=1)

add_executable(bench64 main.cpp)
target_link_libraries(bench64 PRIVATE benchmark::benchmark)
target_compile_definitions(bench64 PRIVATE BENCH_64=1)

add_executable(bench219 main.cpp)
target_link_libraries(bench219 PRIVATE benchmark::benchmark)
target_compile_definitions(bench219 PRIVATE BENCH_219=1)