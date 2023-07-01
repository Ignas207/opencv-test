cmake_minimum_required(VERSION 3.8)
project(display-image)

set(PROJ_NAME "display_image")
set(PROJ_PATH ${CMAKE_SOURCE_DIR})
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJ_NAME} ${PROJ_PATH}/src/testing/display.cpp)

target_compile_options(${PROJ_NAME} PRIVATE
    -Wall 
    -Wextra
    -Wpedantic
    # -fanalyzer
    -Wno-unused-parameter
    -fshort-enums
    -finline-functions
    -Og -g3 -ggdb
    # -O3
)

target_link_libraries(${PROJ_NAME} ${OpenCV_LIBS} )