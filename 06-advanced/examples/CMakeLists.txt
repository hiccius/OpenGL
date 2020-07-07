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

add_executable(06-framebuffers 06-framebuffers.cpp)
target_link_libraries(06-framebuffers PRIVATE utils_06)

add_executable(07-post_processing 07-post_processing.cpp)
target_link_libraries(07-post_processing PRIVATE utils_06)

add_executable(08-kernel_effects 08-kernel_effects.cpp)
target_link_libraries(08-kernel_effects PRIVATE utils_06)

add_executable(09-rearview 09-rearview.cpp)
target_link_libraries(09-rearview PRIVATE utils_06)

add_executable(10-cubemap 10-cubemap.cpp)
target_link_libraries(10-cubemap PRIVATE utils_06)

add_executable(11-mirror 11-mirror.cpp)
target_link_libraries(11-mirror PRIVATE utils_06)

add_executable(12-glass 12-glass.cpp)
target_link_libraries(12-glass PRIVATE utils_06)
