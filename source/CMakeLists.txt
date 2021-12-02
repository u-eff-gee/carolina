include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(tfile_utilities tfile_utilities.cpp)
target_link_libraries(tfile_utilities ${ROOT_LIBRARIES})

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES} ${ROOT_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_library(module module.cpp)
target_link_libraries(module ${ROOT_LIBRARIES})

add_library(mdpp16 mdpp16.cpp)
target_link_libraries(mdpp16 module ${ROOT_LIBRARIES})

add_library(sis3316 sis3316.cpp)
target_link_libraries(sis3316 module ${ROOT_LIBRARIES})

add_library(channel channel.cpp)

add_library(detector detector.cpp)
target_link_libraries(detector channel)

add_library(detector_setup detector_setup.cpp)

add_executable(calibrate_tree calibrate_tree.cpp)
target_include_directories(calibrate_tree PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(calibrate_tree detector module ${Boost_LIBRARIES} command_line_parser detector_setup progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)

add_executable(energy_vs_time energy_vs_time.cpp)
target_include_directories(energy_vs_time PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(energy_vs_time detector module ${Boost_LIBRARIES} command_line_parser detector_setup progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)

add_executable(histograms_1d histograms_1d.cpp)
target_include_directories(histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_1d detector module ${Boost_LIBRARIES} command_line_parser detector_setup progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)

add_executable(histograms_1d_raw histograms_1d_raw.cpp)
target_include_directories(histograms_1d_raw PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_1d_raw detector module ${Boost_LIBRARIES} command_line_parser detector_setup progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)

add_executable(histograms_1d_text histograms_1d_text.cpp)
target_link_libraries(histograms_1d_text ${Boost_LIBRARIES} command_line_parser ${ROOT_LIBRARIES})

add_executable(histograms_2d histograms_2d.cpp)
target_include_directories(histograms_2d PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_2d detector module ${Boost_LIBRARIES} command_line_parser detector_setup progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)

add_executable(multitask multitask.cpp)
target_link_libraries(multitask ${Boost_LIBRARIES} ${ROOT_LIBRARIES} tfile_utilities)

add_executable(split_tree split_tree.cpp)
target_include_directories(split_tree PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(split_tree detector module ${Boost_LIBRARIES} progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities)
