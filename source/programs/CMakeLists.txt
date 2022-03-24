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
include_directories(${CMAKE_SOURCE_DIR}/include/reader)

add_executable(calibrate_tree calibrate_tree.cpp)
target_include_directories(calibrate_tree PUBLIC ${CMAKE_BINARY_DIR}/include/programs)
target_link_libraries(calibrate_tree analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(history history.cpp)
target_include_directories(history PUBLIC ${CMAKE_BINARY_DIR}/include/programs)
target_link_libraries(history analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(energy_vs_time energy_vs_time.cpp)
target_include_directories(energy_vs_time PUBLIC ${CMAKE_BINARY_DIR}/include/programs)
target_link_libraries(energy_vs_time analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_1d histograms_1d.cpp)
target_include_directories(histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include/programs)
target_link_libraries(histograms_1d analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_1d_raw histograms_1d_raw.cpp)
target_include_directories(histograms_1d_raw PUBLIC ${CMAKE_BINARY_DIR}/include/programs ${CMAKE_BINARY_DIR}/include/reader)
target_link_libraries(histograms_1d_raw analysis ${Boost_LIBRARIES} command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp mvlclst progress_printer tree ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)

add_executable(histograms_2d histograms_2d.cpp)
target_include_directories(histograms_2d PUBLIC ${CMAKE_BINARY_DIR}/include/programs)
target_link_libraries(histograms_2d analysis ${Boost_LIBRARIES} coincidence_matrix command_line_parser counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel mdpp16 mdpp16_scp progress_printer ${ROOT_LIBRARIES} sis3316 tfile_utilities v830)