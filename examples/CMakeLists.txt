set(examples "${examples_to_build}")
message(STATUS "Found examples: ${examples}")

# Process subdirectories
foreach(example ${examples})
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${example}/CMakeLists.txt)
        message(STATUS "Processing ${example}")
        add_subdirectory(${example})
    else()
        message(${HIGHLIGHTED_STATUS} "Skipping ${example}: it does not contain a CMakeLists.txt file")
  endif()
endforeach()