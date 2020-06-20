cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-simple_model 01-simple_model.cpp mesh.cpp model.cpp)
target_link_libraries(01-simple_model PRIVATE utils_05)
