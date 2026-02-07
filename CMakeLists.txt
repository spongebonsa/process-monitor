cmake_minimum_required(VERSION 3.10)
project(process_monitor)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(process_monitor src/main.cpp)
target_link_libraries(process_monitor ${CURSES_LIBRARIES})

