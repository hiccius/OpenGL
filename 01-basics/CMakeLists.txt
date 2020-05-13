cmake_minimum_required(VERSION 3.0)

project(1-Basics)

set(EXTRA_INCLUDES ${EXTRA_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/common)
set(EXTRA_SOURCES ${EXTRA_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/common/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/shaderprogram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/vertexdatahandler.cpp)
add_subdirectory(11-Triangle)
