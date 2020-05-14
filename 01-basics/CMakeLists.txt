cmake_minimum_required(VERSION 3.0)

project(01-basics)

if(APPLE)
    add_compile_options(-Wall -Wextra -pedantic-errors -Werrors)
elseif(WIN32)
    add_compile_options(/W4)
endif()

add_subdirectory(utils)
add_subdirectory(01-triangle)
