cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-points 01-points.cpp)
target_link_libraries(01-points PRIVATE utils_07)

add_executable(02-split 02-split.cpp)
target_link_libraries(02-split PRIVATE utils_07)
