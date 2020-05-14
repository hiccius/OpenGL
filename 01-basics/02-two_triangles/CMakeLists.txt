cmake_minimum_required(VERSION 3.0)

project(02-two_triangles)

add_executable(two_triangles main.cpp)

target_link_libraries(two_triangles PRIVATE utils)
