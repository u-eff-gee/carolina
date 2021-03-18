include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(command_line_parser command_line_parser.cpp)
target_link_libraries(command_line_parser ${Boost_LIBRARIES})

add_library(progress_printer progress_printer.cpp)

add_executable(configure_histograms_1d configure_histograms_1d.cpp)
target_include_directories(configure_histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include)

add_executable(multithread_screen multithread_screen.cpp)
target_link_libraries(multithread_screen command_line_parser ${ROOT_LIBRARIES})