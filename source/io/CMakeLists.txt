#     This file is part of carolina.
#
#    carolina is free software: you can redistribute it and/or modify it under the terms of 
#    the GNU General Public License as published by the Free Software Foundation, 
#    either version 3 of the License, or (at your option) any later version.
#
#    carolina is distributed in the hope that it will be useful, but WITHOUT ANY 
#    WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
#    more details.
#
#    You should have received a copy of the GNU General Public License along with 
#    carolina. If not, see <https://www.gnu.org/licenses/>.

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
target_link_libraries(histograms_1d_text ${Boost_LIBRARIES} command_line_parser ${ROOT_LIBRARIES} tfile_utilities)

add_library(polynomial polynomial.cpp)

add_library(progress_printer progress_printer.cpp)

add_executable(split_tree split_tree.cpp)
target_include_directories(split_tree PUBLIC ${CMAKE_BINARY_DIR}/include/io)
target_link_libraries(split_tree analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)