cmake_minimum_required(VERSION 3.10.0)
project(primitive VERSION 0.1.0 LANGUAGES C)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
# find_package(GLEW REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("/utf-8")
endif()
add_executable(primitive main.c stb_image.h stb_image_write.h config.h util.h util.c log.h)
target_link_libraries(primitive glfw glad::glad)

add_subdirectory(gui/)
add_subdirectory(examples/)

add_executable(shape shape.c rasterizer.c triangle.c test_shape.c)