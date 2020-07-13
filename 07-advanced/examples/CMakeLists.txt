cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-points 01-points.cpp)
target_link_libraries(01-points PRIVATE utils_07)

add_executable(02-split 02-split.cpp)
target_link_libraries(02-split PRIVATE utils_07)

add_executable(03-face_orientation 03-face_orientation.cpp)
target_link_libraries(03-face_orientation PRIVATE utils_07)

add_executable(04-uniform_buffer_objects 04-uniform_buffer_objects.cpp)
target_link_libraries(04-uniform_buffer_objects PRIVATE utils_07)

add_executable(05-geometry_shader 05-geometry_shader.cpp)
target_link_libraries(05-geometry_shader PRIVATE utils_07)

add_executable(06-exploding 06-exploding.cpp)
target_link_libraries(06-exploding PRIVATE utils_07)

add_executable(07-visible_normals 07-visible_normals.cpp)
target_link_libraries(07-visible_normals PRIVATE utils_07)
