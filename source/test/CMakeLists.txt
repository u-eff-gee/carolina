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
include_directories(${CMAKE_SOURCE_DIR}/include/test)

add_library(inverse_calibration inverse_calibration.cpp)
target_link_libraries(inverse_calibration ${ROOT_LIBRARIES})

add_executable(sampler sampler.cpp)
target_include_directories(sampler PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(sampler analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel energy_sensitive_detector energy_sensitive_detector_channel inverse_calibration mdpp16 progress_printer ${ROOT_LIBRARIES} sis3316 v830)

add_executable(test_tfile_utilities test_tfile_utilities.cpp)
target_link_libraries(test_tfile_utilities tfile_utilities)

add_executable(test_polynomial test_polynomial.cpp)
target_link_libraries(test_polynomial polynomial)

add_executable(test_histograms_1d_raw test_histograms_1d_raw.cpp)
target_include_directories(test_histograms_1d_raw PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(test_histograms_1d_raw analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel digitizer_module energy_sensitive_detector energy_sensitive_detector_channel mdpp16 ${ROOT_LIBRARIES} sis3316 v830)

add_executable(test_histograms_1d test_histograms_1d.cpp)
target_include_directories(test_histograms_1d PUBLIC ${CMAKE_BINARY_DIR}/include/test)
target_link_libraries(test_histograms_1d analysis ${Boost_LIBRARIES} counter_detector counter_detector_channel digitizer_module energy_sensitive_detector energy_sensitive_detector_channel mdpp16 ${ROOT_LIBRARIES} scaler_module sis3316 v830)