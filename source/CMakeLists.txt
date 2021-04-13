include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_library(mdpp16 mdpp16.cpp)
target_link_libraries(mdpp16 ${ROOT_LIBRARIES})

add_executable(histograms_1d histograms_1d.cpp)
target_include_directories(histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include)
target_link_libraries(histograms_1d mdpp16 ${Boost_LIBRARIES} command_line_parser progress_printer ${ROOT_LIBRARIES})