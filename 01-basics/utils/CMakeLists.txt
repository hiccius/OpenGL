cmake_minimum_required(VERSION 3.0)

project(utils)

add_library(utils
    src/shader.cpp
    src/shaderprogram.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_include_directories(utils PUBLIC include ${EXTRA_INCLUDES})
target_compile_options(utils PUBLIC -Wall -Wextra -pedantic-errors -Werror)
