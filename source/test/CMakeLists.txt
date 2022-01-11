include_directories(${CMAKE_SOURCE_DIR}/include/analysis)
include_directories(${CMAKE_SOURCE_DIR}/include/detectors)
include_directories(${CMAKE_SOURCE_DIR}/include/experiments)
include_directories(${CMAKE_SOURCE_DIR}/include/io)
include_directories(${CMAKE_SOURCE_DIR}/include/modules)
include_directories(${CMAKE_SOURCE_DIR}/include/test)

add_library(inverse_calibration inverse_calibration.cpp)
target_link_libraries(inverse_calibration ${ROOT_LIBRARIES})

add_executable(sampler sampler.cpp)
target_include_directories(sampler PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(sampler analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel inverse_calibration mdpp16 progress_printer ${ROOT_LIBRARIES} v830)
