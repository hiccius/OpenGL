cmake_minimum_required(VERSION 3.0)

project(02-textures)

if(APPLE)
    add_compile_options(-Wall -Wextra -pedantic-errors -Werror)
elseif(WIN32)
    add_compile_options(/W4)
endif()

add_compile_definitions(PROJECT_DIR="${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(utils)
add_subdirectory(examples)

add_custom_target(02-textures ALL
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/shaders
                          ${CMAKE_CURRENT_BINARY_DIR}/shaders
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                          ${CMAKE_CURRENT_SOURCE_DIR}/resources
                          ${CMAKE_CURRENT_BINARY_DIR}/resources)
