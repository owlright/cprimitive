cmake_minimum_required(VERSION 3.19.0)
project(primitive VERSION 0.1.0 LANGUAGES C)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("/utf-8")
endif()
add_library(primitive STATIC util.c shape.c rasterizer.c triangle.c line.c)
target_link_libraries(primitive PRIVATE glfw glad::glad)

include(cmake/macros.cmake)
# Scan module libraries
subdirlist(examples_to_build ${CMAKE_CURRENT_SOURCE_DIR}/examples)
# message(STATUS "Found examples: ${examples_to_build}")
add_subdirectory(examples/)

add_executable(shape test_shape.c)
target_link_libraries(shape PRIVATE primitive glfw glad::glad)

add_subdirectory(test)

