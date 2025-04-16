cmake_minimum_required(VERSION 3.10)
project(OrderMatchingEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

include_directories(src)

add_executable(OrderMatchingEngine
    src/main.cpp
)   

target_link_libraries(OrderMatchingEngine 
    ncurses
)

# enable_testing()
# add_executable(tests test/tests.cpp)
# find_package(Catch2 REQUIRED)
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
# target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src)