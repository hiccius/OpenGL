cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-fallen_container 01-fallen_container.cpp)
target_link_libraries(01-fallen_container PRIVATE utils_03)

add_executable(02-moving_container 02-moving_container.cpp)
target_link_libraries(02-moving_container PRIVATE utils_03)

add_executable(03-dancing_containers 03-dancing_containers.cpp)
target_link_libraries(03-dancing_containers PRIVATE utils_03)

add_executable(04-lying_container 04-lying_container.cpp)
target_link_libraries(04-lying_container PRIVATE utils_03)

add_executable(05-cube 05-cube.cpp)
target_link_libraries(05-cube PRIVATE utils_03)

add_executable(06-multiple_cubes 06-multiple_cubes.cpp)
target_link_libraries(06-multiple_cubes PRIVATE utils_03)

add_executable(07-rotating_camera 07-rotating_camera.cpp)
target_link_libraries(07-rotating_camera PRIVATE utils_03)

add_executable(08-free_camera 08-free_camera.cpp)
target_link_libraries(08-free_camera PRIVATE utils_03)
