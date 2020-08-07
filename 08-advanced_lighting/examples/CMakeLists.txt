cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-blinn 01-blinn.cpp)
target_link_libraries(01-blinn PRIVATE utils_08)
