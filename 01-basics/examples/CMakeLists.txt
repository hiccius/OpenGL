cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-triangle 01-triangle.cpp)
target_link_libraries(01-triangle PRIVATE utils)

add_executable(02-two_triangles 02-two_triangles.cpp)
target_link_libraries(02-two_triangles PRIVATE utils)

add_executable(03-two_independent_triangles 03-two_independent_triangles.cpp)
target_link_libraries(03-two_independent_triangles PRIVATE utils)
