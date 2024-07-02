add_executable(test_line test_line.c)
target_include_directories(test_line PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(test_line PRIVATE primitive)
