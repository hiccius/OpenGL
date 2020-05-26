cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-fallen_container 01-fallen_container.cpp)
target_link_libraries(01-fallen_container PRIVATE utils_03)

add_executable(02-moving_container 02-moving_container.cpp)
target_link_libraries(02-moving_container PRIVATE utils_03)

add_executable(03-dancing_containers 03-dancing_containers.cpp)
target_link_libraries(03-dancing_containers PRIVATE utils_03)
