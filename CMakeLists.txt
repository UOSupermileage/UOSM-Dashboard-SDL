set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(UOSM-Dashboard-SDL C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get GoogleTest dependency
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Compile for debugging
message(STATUS "Minimal optimization, debug info included")
add_compile_options(-Og -g)

include_directories(
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/lv_drivers   
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/Inc
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI/Data
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI/Utils
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Core/UI/Components
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/UOSM-Core/Inc
    ${CMAKE_SOURCE_DIR}/UOSM-Dashboard/Drivers
)

file(GLOB_RECURSE SOURCES "main/*.*" "lv_drivers/*.*")
file(GLOB_RECURSE UI_SOURCES "UOSM-Dashboard/Core/UI/*.*" "UOSM-Dashboard/Drivers/Fonts/*.*" "UOSM-Dashboard/Drivers/lvgl/*.*")

# Files to test
file(GLOB_RECURSE TEST_SOURCES "test/*.*")

add_subdirectory(lv_drivers)
add_subdirectory(UOSM-Dashboard/Drivers/lvgl)

add_link_options(-Wl)

# find_file(SDL2_INCLUDE_DIRS NAME SDL.h HINTS SDL2)
# find_library(SDL2_LIBRARY NAME SDL2)
# message ([STATUS] "SDL2_INCLUDE_DIRS" ${SDL2_INCLUDE_DIRS})
# message ([STATUS] "SDL2_LIBRARIES" ${SDL2_LIBRARIES})

find_package(SDL2 REQUIRED)

enable_testing()

add_executable(UOSM-Dashboard-SDL ${SOURCES} ${UI_SOURCES})
add_executable(UOSM-Dashboard-Test ${TEST_SOURCES} ${UI_SOURCES})

set_target_properties(UOSM-Dashboard-SDL PROPERTIES LINKER_LANGUAGE CXX)

include_directories(UOSM-Dashboard-SDL ${SDL2_INCLUDE_DIRS})
target_link_libraries(UOSM-Dashboard-SDL ${SDL2_LIBRARIES} GTest::gtest_main)

target_link_libraries(UOSM-Dashboard-Test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(UOSM-Dashboard-Test)