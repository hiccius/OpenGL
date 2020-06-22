cmake_minimum_required(VERSION 3.3)

project(ThirdPartyLibs)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Assimp tests")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Shared libraries")
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "Debug postfix")
add_subdirectory(assimp)
add_subdirectory(GLAD)
add_subdirectory(GLFW)
add_subdirectory(GLM)
add_subdirectory(STB)

add_library(OpenGLThirdParty INTERFACE)
target_link_libraries(OpenGLThirdParty INTERFACE assimp glfw glad glm stb_image)

set(EXTRA_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/GLAD/src/glad.c
    CACHE INTERNAL "")
