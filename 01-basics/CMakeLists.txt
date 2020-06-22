cmake_minimum_required(VERSION 3.3)

project(01-basics)

if(APPLE)
    add_compile_options(-Wall -Wextra -pedantic-errors -Werror)
elseif(WIN32)
    add_compile_options(/W4)
endif()

add_subdirectory(utils)
add_subdirectory(examples)

add_custom_target(01-basics ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/shaders
                          ${CMAKE_CURRENT_BINARY_DIR}/shaders)
