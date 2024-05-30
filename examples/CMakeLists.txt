cmake_minimum_required(VERSION 3.10.0)
project(offscreen LANGUAGES C)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(offscreen offscreen.c ../stb_image.h ../stb_image_write.h)
add_executable(renderImage render_image.c ../stb_image.h)
target_link_libraries(offscreen glfw glad::glad)
target_link_libraries(renderImage glfw glad::glad)
