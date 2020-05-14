cmake_minimum_required(VERSION 3.0)

project(ThirdPartyLibs)

add_subdirectory(GLAD)
add_subdirectory(GLFW)

add_library(OpenGLThirdParty INTERFACE)
target_link_libraries(OpenGLThirdParty INTERFACE glfw glad)

set(EXTRA_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/GLAD/src/glad.c
    CACHE INTERNAL "")
