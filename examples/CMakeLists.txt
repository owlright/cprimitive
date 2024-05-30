cmake_minimum_required(VERSION 3.10.0)
project(offscreen LANGUAGES C)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(offscreen offscreen.c ../stb_image.h ../stb_image_write.h)
target_link_libraries(offscreen glfw glad::glad)