cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(01-triangle 01-triangle.cpp)
target_link_libraries(01-triangle PRIVATE utils_01)

add_executable(02-two_triangles 02-two_triangles.cpp)
target_link_libraries(02-two_triangles PRIVATE utils_01)

add_executable(03-two_independent_triangles 03-two_independent_triangles.cpp)
target_link_libraries(03-two_independent_triangles PRIVATE utils_01)

add_executable(04-rectangle 04-rectangle.cpp)
target_link_libraries(04-rectangle PRIVATE utils_01)

add_executable(05-colored_triangle 05-colored_triangle.cpp)
target_link_libraries(05-colored_triangle PRIVATE utils_01)

add_executable(06-changing_triangle 06-changing_triangle.cpp)
target_link_libraries(06-changing_triangle PRIVATE utils_01)

add_executable(07-rainbow_triangle 07-rainbow_triangle.cpp)
target_link_libraries(07-rainbow_triangle PRIVATE utils_01)

add_executable(08-flipped_moved_triangle 08-flipped_moved_triangle.cpp)
target_link_libraries(08-flipped_moved_triangle PRIVATE utils_01)

add_executable(09-position_dependant_colored_triangle 09-position_dependant_colored_triangle.cpp)
target_link_libraries(09-position_dependant_colored_triangle PRIVATE utils_01)
