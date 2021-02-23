add_library(progress_printer progress_printer.cpp)
target_include_directories(progress_printer PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(histograms histograms.cpp)
target_include_directories(histograms PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(histograms ${Boost_LIBRARIES} progress_printer ${ROOT_LIBRARIES})