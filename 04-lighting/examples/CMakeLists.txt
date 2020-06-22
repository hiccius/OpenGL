cmake_minimum_required(VERSION 3.3)

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

add_executable(07-lighting_maps 07-lighting_maps.cpp)
target_link_libraries(07-lighting_maps PRIVATE utils_04)

add_executable(08-emission_maps 08-emission_maps.cpp)
target_link_libraries(08-emission_maps PRIVATE utils_04)

add_executable(09-directional_light 09-directional_light.cpp)
target_link_libraries(09-directional_light PRIVATE utils_04)

add_executable(10-point_light 10-point_light.cpp)
target_link_libraries(10-point_light PRIVATE utils_04)

add_executable(11-spotlight 11-spotlight.cpp)
target_link_libraries(11-spotlight PRIVATE utils_04)

add_executable(12-flashlight 12-flashlight.cpp)
target_link_libraries(12-flashlight PRIVATE utils_04)

add_executable(13-full_scene 13-full_scene.cpp 13-atmosphere.cpp)
target_link_libraries(13-full_scene PRIVATE utils_04)
