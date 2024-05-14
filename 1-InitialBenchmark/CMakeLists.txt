cmake_minimum_required (VERSION 3.14)

project (benchmarks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) 

add_executable(benchmarks benchmark.cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../benchmark ${CMAKE_CURRENT_BINARY_DIR}/benchmark)
target_link_libraries(benchmarks benchmark::benchmark)

target_link_libraries(benchmarks ${CMAKE_CURRENT_SOURCE_DIR}/InitialBenchmark/x64/Debug/InitialBenchmark.lib)