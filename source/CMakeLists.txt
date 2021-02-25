include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_executable(histograms histograms.cpp)
target_link_libraries(histograms command_line_parser progress_printer ${ROOT_LIBRARIES})