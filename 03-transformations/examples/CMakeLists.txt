cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-fallen_cube 01-fallen_cube.cpp)
target_link_libraries(01-fallen_cube PRIVATE utils_03)

add_executable(02-moving_cube 02-moving_cube.cpp)
target_link_libraries(02-moving_cube PRIVATE utils_03)

add_executable(03-dancing_cubes 03-dancing_cubes.cpp)
target_link_libraries(03-dancing_cubes PRIVATE utils_03)
