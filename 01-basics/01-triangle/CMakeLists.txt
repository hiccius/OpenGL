cmake_minimum_required(VERSION 3.0)

project(01-triangle)

add_executable(triangle main.cpp)

target_link_libraries(triangle utils)
target_compile_options(triangle PRIVATE -Wall -Wextra -pedantic-errors -Werror)
