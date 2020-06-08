cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-basic_scene 01-basic_scene.cpp)
target_link_libraries(01-basic_scene PRIVATE utils_04)

add_executable(02-phong 02-phong.cpp)
target_link_libraries(02-phong PRIVATE utils_04)

add_executable(03-view_space 03-view_space.cpp)
target_link_libraries(03-view_space PRIVATE utils_04)

add_executable(04-gouraud 04-gouraud.cpp)
target_link_libraries(04-gouraud PRIVATE utils_04)

add_executable(05-materials 05-materials.cpp)
target_link_libraries(05-materials PRIVATE utils_04)

add_executable(06-cyan_plastic 06-cyan_plastic.cpp)
target_link_libraries(06-cyan_plastic PRIVATE utils_04)
