cmake_minimum_required(VERSION 3.10)
project(carolina VERSION 0.2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

set(ANALYSIS "analysis_78Kr.hpp" CACHE STRING "Set name of header file in ${CMAKE_SOURCE_DIR}/include/experiments/ that contains the analysis configuration. Default: 'analysis_78Kr.hpp'.")

add_compile_options(-Wall -Wextra)
option(BUILD_TESTS "Build unit tests. Default: ON" ON)
if(BUILD_TESTS)
    add_compile_options(-Wall -Wextra -ftest-coverage --coverage)
    link_libraries(gcov)
endif(BUILD_TESTS)

add_subdirectory(source/analysis)
add_subdirectory(source/detectors)
add_subdirectory(source/io)
add_subdirectory(source/modules)
add_subdirectory(source/programs)
if(BUILD_TESTS)
    add_subdirectory(source/test)
endif(BUILD_TESTS)

configure_file(include/io/split_tree.hpp.in include/io/split_tree.hpp)
configure_file(include/programs/calibrate_tree.hpp.in include/programs/calibrate_tree.hpp)
configure_file(include/programs/energy_vs_time.hpp.in include/programs/energy_vs_time.hpp)
configure_file(include/programs/histograms_1d.hpp.in include/programs/histograms_1d.hpp)
configure_file(include/programs/histograms_1d_raw.hpp.in include/programs/histograms_1d_raw.hpp)
configure_file(include/programs/histograms_2d.hpp.in include/programs/histograms_2d.hpp)
configure_file(include/programs/history.hpp.in include/programs/history.hpp)
configure_file(include/test/sampler.hpp.in include/test/sampler.hpp)

enable_testing()
add_test(sample_test_data sampler --n 100)
add_test(create_raw_histograms histograms_1d_raw test.root --output test_raw.root)
add_test(calibrate_test_data calibrate_tree test.root --output test_cal.root --log)
add_test(create_histograms histograms_1d test_cal.log --output test_hist.root --log)