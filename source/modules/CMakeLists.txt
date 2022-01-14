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

include_directories(${CMAKE_SOURCE_DIR}/include/modules)

# Abstract modules
add_library(digitizer_module digitizer_module.cpp)
target_link_libraries(digitizer_module ${ROOT_LIBRARIES})

add_library(scaler_module scaler_module.cpp)
target_link_libraries(scaler_module ${ROOT_LIBRARIES})

# Module implementations
add_library(mdpp16 mdpp16.cpp)
target_link_libraries(mdpp16 digitizer_module ${ROOT_LIBRARIES})

add_library(sis3316 sis3316.cpp)
target_link_libraries(sis3316 digitizer_module ${ROOT_LIBRARIES})

add_library(v830 v830.cpp)
target_link_libraries(v830 scaler_module ${ROOT_LIBRARIES})