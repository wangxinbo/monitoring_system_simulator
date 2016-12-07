cmake_minimum_required(VERSION 3.2)
project(generate)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp)

add_executable(generate ${SOURCE_FILES} src/Generator.cpp src/Generator.hpp src/Printer.cpp src/Printer.hpp)
