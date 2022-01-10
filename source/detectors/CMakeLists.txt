include_directories(${CMAKE_SOURCE_DIR}/include/detectors)

# Abstract detector and channel
add_library(channel channel.cpp)

add_library(detector detector.cpp)
target_link_libraries(detector channel)

# Specific detectors and channels
add_library(counter_detector_channel counter_detector_channel.cpp)
target_link_libraries(counter_detector_channel channel)

add_library(energy_sensitive_detector_channel energy_sensitive_detector_channel.cpp)
target_link_libraries(energy_sensitive_detector_channel channel)

add_library(counter_detector counter_detector.cpp)
target_link_libraries(counter_detector channel detector)

add_library(energy_sensitive_detector energy_sensitive_detector.cpp)
target_link_libraries(energy_sensitive_detector channel detector)
