include_directories(${CMAKE_SOURCE_DIR}/include/analysis)
include_directories(${CMAKE_SOURCE_DIR}/include/detectors)
include_directories(${CMAKE_SOURCE_DIR}/include/experiments)
include_directories(${CMAKE_SOURCE_DIR}/include/io)
include_directories(${CMAKE_SOURCE_DIR}/include/modules)
include_directories(${CMAKE_SOURCE_DIR}/include/test)

enable_testing()

add_library(inverse_calibration inverse_calibration.cpp)
target_link_libraries(inverse_calibration ${ROOT_LIBRARIES})

add_executable(sampler sampler.cpp)
target_include_directories(sampler PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(sampler analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel inverse_calibration mdpp16 progress_printer ${ROOT_LIBRARIES} v830)

add_executable(test_tfile_utilities test_tfile_utilities.cpp)
target_link_libraries(test_tfile_utilities tfile_utilities)

add_test(NAME tfile_utilities COMMAND test_tfile_utilities)
add_test(NAME sample_test_data COMMAND sampler --n 100)
add_test(NAME create_raw_histograms COMMAND histograms_1d_raw test.root --output test_raw.root)
add_test(NAME calibrate_test_data COMMAND calibrate_tree test.root --output test_cal.root --log --block 100)
add_test(NAME create_histograms COMMAND histograms_1d test_cal.log --output test_hist.root --log)
