cmake_minimum_required(VERSION 3.3)

set(CMAKE_POLICY_DEFAULT_CMP0063 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_subdirectory(third-party)
add_subdirectory(01-basics)
add_subdirectory(02-textures)
add_subdirectory(03-space)
add_subdirectory(04-lighting)
add_subdirectory(05-models)
add_subdirectory(06-buffers)
add_subdirectory(07-advanced)
