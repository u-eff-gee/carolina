include_directories(${CMAKE_SOURCE_DIR}/include/analysis)
include_directories(${CMAKE_SOURCE_DIR}/include/detectors)
include_directories(${CMAKE_SOURCE_DIR}/include/experiments)
include_directories(${CMAKE_SOURCE_DIR}/include/modules)

add_executable(sampler sampler.cpp)
target_include_directories(sampler PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(sampler analysis ${ROOT_LIBRARIES} counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 v830)
