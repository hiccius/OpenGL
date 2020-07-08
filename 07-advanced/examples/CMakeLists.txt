cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-points 01-points.cpp)
target_link_libraries(01-points PRIVATE utils_07)
