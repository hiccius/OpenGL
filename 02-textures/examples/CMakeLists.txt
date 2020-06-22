cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-wooden_container 01-wooden_container.cpp)
target_link_libraries(01-wooden_container PRIVATE utils_02)

add_executable(02-happy_container 02-happy_container.cpp)
target_link_libraries(02-happy_container PRIVATE utils_02)

add_executable(03-reversed_face 03-reversed_face.cpp)
target_link_libraries(03-reversed_face PRIVATE utils_02)

add_executable(04-multiple_faces 04-multiple_faces.cpp)
target_link_libraries(04-multiple_faces PRIVATE utils_02)

add_executable(05-zoomed_textures 05-zoomed_textures.cpp)
target_link_libraries(05-zoomed_textures PRIVATE utils_02)

add_executable(06-weighted_textures 06-weighted_textures.cpp)
target_link_libraries(06-weighted_textures PRIVATE utils_02)
