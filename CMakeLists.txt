cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

set(ANALYSIS "analysis.hpp" CACHE STRING "Set name of header file in ${CMAKE_SOURCE_DIR}/include/ that contains the analysis configuration. Default: 'analysis.hpp'.")

add_compile_options(-Wall -Wextra)

add_subdirectory(source)

configure_file(include/calibrate_tree.hpp.in include/calibrate_tree.hpp)
configure_file(include/energy_vs_event_number.hpp.in include/energy_vs_event_number.hpp)
configure_file(include/energy_vs_time.hpp.in include/energy_vs_time.hpp)
configure_file(include/histograms_1d.hpp.in include/histograms_1d.hpp)
configure_file(include/histograms_1d_raw.hpp.in include/histograms_1d_raw.hpp)
configure_file(include/histograms_2d.hpp.in include/histograms_2d.hpp)
configure_file(include/split_tree.hpp.in include/split_tree.hpp)