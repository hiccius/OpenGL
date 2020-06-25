cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-depth_test 01-depth_test.cpp)
target_link_libraries(01-depth_test PRIVATE utils_06)

add_executable(02-stencil_test 02-stencil_test.cpp)
target_link_libraries(02-stencil_test PRIVATE utils_06)
