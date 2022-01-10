include_directories(${CMAKE_SOURCE_DIR}/include/analysis)
include_directories(${CMAKE_SOURCE_DIR}/include/detectors)
include_directories(${CMAKE_SOURCE_DIR}/include/modules)

add_library(coincidence_matrix coincidence_matrix.cpp)

add_library(analysis analysis.cpp)