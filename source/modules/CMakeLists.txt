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