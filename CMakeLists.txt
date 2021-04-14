cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

set(DETECTOR_SETUP "detector_setup.hpp" CACHE STRING "Set name of header file in ${CMAKE_SOURCE_DIR}/include/ that contains the detector setup. Default: 'detector_setup.hpp'.")

add_subdirectory(source)

configure_file(include/histograms_1d.hpp.in include/histograms_1d.hpp)
configure_file(include/histograms_2d.hpp.in include/histograms_2d.hpp)