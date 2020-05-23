cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-wooden_container 01-wooden_container.cpp)
target_link_libraries(01-wooden_container PRIVATE utils_02)

add_executable(02-happy_container 02-happy_container.cpp)
target_link_libraries(02-happy_container PRIVATE utils_02)
