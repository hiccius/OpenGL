cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-basic_scene 01-basic_scene.cpp)
target_link_libraries(01-basic_scene PRIVATE utils_04)
