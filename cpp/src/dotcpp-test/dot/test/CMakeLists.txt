cmake_minimum_required(VERSION 3.7.2)

file(GLOB_RECURSE dotcpp_test_files "*.cpp" "*.hpp")

SET(GCC_COVERAGE_LINK_FLAGS "-lresolv -lrt -pthread")

add_executable(dotcpp_tests main.cpp ${dotcpp_test_files})
target_link_libraries(dotcpp_tests BoostLib)
target_link_libraries(dotcpp_tests dotcpp_api ${GCC_COVERAGE_LINK_FLAGS})
