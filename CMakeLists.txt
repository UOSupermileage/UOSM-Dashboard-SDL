set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(UOSM-Dashboard-SDL C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

message(STATUS "Minimal optimization, debug info included")
add_compile_options(-Og -g)

include_directories(
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/lv_drivers   
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/Inc
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI/Data
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI/Utils
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/UOSM-Core/Inc
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Drivers
)

file(GLOB_RECURSE SOURCES "main/*.*" "UOSM-Dashboard/Core/UI/*.*" "UOSM-Dashboard/Drivers/Fonts/*.*" "lv_drivers/*.*" "UOSM-Dashboard/Drivers/lvgl/*.*")

add_subdirectory(lv_drivers)
add_subdirectory(UOSM-Dashboard/Drivers/lvgl)

add_link_options(-Wl)

# find_file(SDL2_INCLUDE_DIRS NAME SDL.h HINTS SDL2)
# find_library(SDL2_LIBRARY NAME SDL2)
# message ([STATUS] "SDL2_INCLUDE_DIRS" ${SDL2_INCLUDE_DIRS})
# message ([STATUS] "SDL2_LIBRARIES" ${SDL2_LIBRARIES})

find_package(SDL2 REQUIRED)

add_executable(UOSM-Dashboard-SDL ${SOURCES})

set_target_properties(UOSM-Dashboard-SDL PROPERTIES LINKER_LANGUAGE CXX)

include_directories(UOSM-Dashboard-SDL ${SDL2_INCLUDE_DIRS})
target_link_libraries(UOSM-Dashboard-SDL ${SDL2_LIBRARIES})