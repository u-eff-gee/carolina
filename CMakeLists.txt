cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

set(DETECTOR_SETUP "detector_setup.hpp" CACHE STRING "Set name of header file in ${CMAKE_SOURCE_DIR}/include/ that contains the detector setup. Default: 'detector_setup.hpp'.")

add_subdirectory(source)

configure_file(code_generation/CMakeLists.txt.in code_generation/CMakeLists.txt)
configure_file(include/configure_histograms_1d.hpp.in ${CMAKE_BINARY_DIR}/include/configure_histograms_1d.hpp)
