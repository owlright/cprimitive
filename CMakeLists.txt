cmake_minimum_required(VERSION 3.10.0)
project(primitive VERSION 0.1.0 LANGUAGES C)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()
add_executable(primitive main.c stb_image.h stb_image_write.h config.h util.h util.c tlog.h tlog.c)
target_link_libraries(primitive glfw glad::glad GLEW::GLEW)

add_subdirectory(gui/)