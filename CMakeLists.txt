cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

add_subdirectory(source)