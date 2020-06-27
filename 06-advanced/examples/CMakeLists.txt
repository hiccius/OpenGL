cmake_minimum_required(VERSION 3.3)

project(examples)

add_executable(01-depth_test 01-depth_test.cpp)
target_link_libraries(01-depth_test PRIVATE utils_06)

add_executable(02-stencil_test 02-stencil_test.cpp)
target_link_libraries(02-stencil_test PRIVATE utils_06)

add_executable(03-transparencies 03-transparencies.cpp)
target_link_libraries(03-transparencies PRIVATE utils_06)

add_executable(04-blending 04-blending.cpp)
target_link_libraries(04-blending PRIVATE utils_06)

add_executable(05-face_culling 05-face_culling.cpp)
target_link_libraries(05-face_culling PRIVATE utils_06)
