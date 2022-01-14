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

include_directories(${CMAKE_SOURCE_DIR}/include/detectors)

# Abstract detector and channel
add_library(channel channel.cpp)

add_library(detector detector.cpp)
target_link_libraries(detector channel)

# Specific detectors and channels
add_library(counter_detector_channel counter_detector_channel.cpp)
target_link_libraries(counter_detector_channel channel)

add_library(energy_sensitive_detector_channel energy_sensitive_detector_channel.cpp)
target_link_libraries(energy_sensitive_detector_channel channel)

add_library(counter_detector counter_detector.cpp)
target_link_libraries(counter_detector channel detector)

add_library(energy_sensitive_detector energy_sensitive_detector.cpp)
target_link_libraries(energy_sensitive_detector channel detector)
