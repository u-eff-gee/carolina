include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(tfile_utilities tfile_utilities.cpp)
target_link_libraries(tfile_utilities ${ROOT_LIBRARIES})

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES} ${ROOT_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_library(digitizer_module digitizer_module.cpp)
target_link_libraries(digitizer_module ${ROOT_LIBRARIES})

add_library(mdpp16 mdpp16.cpp)
target_link_libraries(mdpp16 digitizer_module ${ROOT_LIBRARIES})

add_library(sis3316 sis3316.cpp)
target_link_libraries(sis3316 digitizer_module ${ROOT_LIBRARIES})

add_library(scaler_module scaler_module.cpp)
target_link_libraries(scaler_module ${ROOT_LIBRARIES})

add_library(v830 v830.cpp)
target_link_libraries(v830 scaler_module ${ROOT_LIBRARIES})

add_library(channel channel.cpp)

add_library(coincidence_matrix coincidence_matrix.cpp)

add_library(counter_detector_channel counter_detector_channel.cpp)
target_link_libraries(counter_detector_channel channel)

add_library(energy_sensitive_detector_channel energy_sensitive_detector_channel.cpp)
target_link_libraries(energy_sensitive_detector_channel channel)

add_library(detector detector.cpp)
target_link_libraries(detector channel)

add_library(counter_detector counter_detector.cpp)
target_link_libraries(counter_detector channel detector)

add_library(energy_sensitive_detector energy_sensitive_detector.cpp)
target_link_libraries(energy_sensitive_detector channel detector)

add_library(analysis analysis.cpp)

add_executable(calibrate_tree calibrate_tree.cpp)
target_include_directories(calibrate_tree PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(calibrate_tree analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(history history.cpp)
target_include_directories(history PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(history analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(energy_vs_time energy_vs_time.cpp)
target_include_directories(energy_vs_time PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(energy_vs_time analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_1d histograms_1d.cpp)
target_include_directories(histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_1d analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_1d_raw histograms_1d_raw.cpp)
target_include_directories(histograms_1d_raw PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_1d_raw analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_1d_text histograms_1d_text.cpp)
target_link_libraries(histograms_1d_text ${Boost_LIBRARIES} command_line_parser ${ROOT_LIBRARIES})

add_executable(histograms_2d histograms_2d.cpp)
target_include_directories(histograms_2d PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_2d analysis ${Boost_LIBRARIES} coincidence_matrix command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(split_tree split_tree.cpp)
target_include_directories(split_tree PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(split_tree analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)
