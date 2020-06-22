cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-simple_model 01-simple_model.cpp)
target_link_libraries(01-simple_model PRIVATE utils_05)

add_executable(02-lighting 02-lighting.cpp)
target_link_libraries(02-lighting PRIVATE utils_05)
