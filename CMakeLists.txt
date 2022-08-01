#     This file is part of carolina.
#
#    carolina is free software: you can redistribute it and/or modify it under the terms of 
#    the GNU General Public License as published by the Free Software Foundation, 
#    either version 3 of the License, or (at your option) any later version.
#
#    carolina is distributed in the hope that it will be useful, but WITHOUT ANY 
#    WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
#    more details.
#
#    You should have received a copy of the GNU General Public License along with 
#    carolina. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

set(ANALYSIS "test" CACHE STRING "Set name of header file (without the '.hpp' suffix) in ${CMAKE_SOURCE_DIR}/include/experiments/ that contains the analysis configuration. Default: 'test'.")
set(READER "tree" CACHE STRING "Determine whether raw data should be read from a ROOT TTree object ('tree') or an MVLC listfile ('mvlclst', not implemented at the moment).")

add_compile_options(-Wall -Wextra)
option(BUILD_TESTS "Build unit tests. Default: ON" ON)
if(BUILD_TESTS)
    add_compile_options(-Wall -Wextra -ftest-coverage --coverage)
    link_libraries(gcov)
    enable_testing()
endif(BUILD_TESTS)

add_subdirectory(source/analysis)
add_subdirectory(source/detectors)
add_subdirectory(source/io)
add_subdirectory(source/modules)
add_subdirectory(source/programs)
add_subdirectory(source/reader)
if(BUILD_TESTS)
    add_subdirectory(source/test)
    add_test(NAME tfile_utilities COMMAND test_tfile_utilities)
    add_test(NAME sample_test_data COMMAND sampler --output test.root --n 100)
    add_test(NAME split_test_data COMMAND split_tree test.root --output test_part --n 4 --log)
    add_test(NAME create_raw_histograms COMMAND histograms_1d_raw test_part.log --output test_raw.root --list)
    add_test(NAME test_raw_histograms COMMAND test_histograms_1d_raw test_raw.root --n 100)
    add_test(NAME calibrate_test_data COMMAND calibrate_tree test_part.log --output test_cal.root --log --list --block 100)
    add_test(NAME create_1d_histograms COMMAND histograms_1d test_cal.log --output test_1d.root --list)
    add_test(NAME calibrate_and_create_1d_histograms COMMAND histograms_1d test.root --output test_1d_cal.root --calibrate)
    add_test(NAME test_1d_histograms_from_calibrated_trees COMMAND test_histograms_1d test_1d.root --n 100)
    add_test(NAME test_1d_histograms_from_direct_histogramming COMMAND test_histograms_1d test_1d_cal.root --n 100)
    add_test(NAME create_2d_histograms COMMAND histograms_2d test_cal.log --output test_2d.root --list)
    add_test(NAME time_calibration COMMAND energy_vs_time test_cal.log --output test_et.root --rebin_energy 32 --list)
    add_test(NAME history COMMAND history test_cal.log --output test_history.root --list)
    add_test(NAME text_files_single_column COMMAND histograms_1d_text test_1d.root --suffix single_column)
    add_test(NAME text_files_two_column COMMAND histograms_1d_text test_1d.root --separator " " --suffix two_column)
    add_test(NAME polynomial COMMAND test_polynomial)
endif(BUILD_TESTS)

configure_file(include/io/split_tree.hpp.in include/io/split_tree.hpp)
configure_file(include/programs/calibrate_tree.hpp.in include/programs/calibrate_tree.hpp)
configure_file(include/programs/energy_vs_time.hpp.in include/programs/energy_vs_time.hpp)
configure_file(include/programs/histograms_1d.hpp.in include/programs/histograms_1d.hpp)
configure_file(include/programs/histograms_1d_raw.hpp.in include/programs/histograms_1d_raw.hpp)
configure_file(include/programs/histograms_2d.hpp.in include/programs/histograms_2d.hpp)
configure_file(include/programs/history.hpp.in include/programs/history.hpp)
configure_file(include/programs/mvlclst_to_root.hpp.in include/programs/mvlclst_to_root.hpp)
configure_file(include/test/sampler.hpp.in include/test/sampler.hpp)
configure_file(include/test/test_histograms_1d_raw.hpp.in include/test/test_histograms_1d_raw.hpp)
configure_file(include/test/test_histograms_1d.hpp.in include/test/test_histograms_1d.hpp)