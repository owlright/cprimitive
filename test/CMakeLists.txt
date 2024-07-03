include_directories(test_line PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(test_line test_line.c)
target_link_libraries(test_line PRIVATE primitive)

add_executable(test_rgb2gray test_rgb2gray.c)
target_link_libraries(test_rgb2gray PRIVATE primitive)