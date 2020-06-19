cmake_minimum_required(VERSION 3.0)

project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0077 NEW)

add_subdirectory(third-party)
add_subdirectory(01-basics)
add_subdirectory(02-textures)
add_subdirectory(03-space)
add_subdirectory(04-lighting)
add_subdirectory(05-models)
