include_directories(${CMAKE_SOURCE_DIR}/include/analysis)
include_directories(${CMAKE_SOURCE_DIR}/include/detectors)
include_directories(${CMAKE_SOURCE_DIR}/include/experiments)
include_directories(${CMAKE_SOURCE_DIR}/include/io)
include_directories(${CMAKE_SOURCE_DIR}/include/modules)

add_library(tfile_utilities tfile_utilities.cpp)
target_link_libraries(tfile_utilities ${ROOT_LIBRARIES})

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES} ${ROOT_LIBRARIES})

add_executable(histograms_1d_text histograms_1d_text.cpp)
target_link_libraries(histograms_1d_text ${Boost_LIBRARIES} command_line_parser ${ROOT_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_executable(split_tree split_tree.cpp)
target_include_directories(split_tree PUBLIC ${CMAKE_BINARY_DIR}/include/io)
target_link_libraries(split_tree analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)