cmake_minimum_required(VERSION 3.10)
project(OrderMatchingEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(OrderMatchingEngine
    src/main.cpp
)   