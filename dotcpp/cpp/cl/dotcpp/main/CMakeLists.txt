cmake_minimum_required (VERSION 3.7.2)

set(CMAKE_CXX_FLAGS "-fPIC")

file(GLOB_RECURSE dotcpp_api_files "*.cpp" "*.hpp")

add_library(dotcpp_api ${dotcpp_api_files})

#copy executable to bin directory
add_custom_command(TARGET dotcpp_api 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dotcpp_api> "${PROJECT_SOURCE_DIR}/${BIN_FOLDER}")
