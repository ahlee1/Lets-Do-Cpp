cmake_minimum_required(VERSION 3.10)

project(SocketLibray VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_config.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_config.hpp")

add_executable(SocketLibray source/main.cpp)