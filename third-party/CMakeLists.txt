cmake_minimum_required(VERSION 3.0)

project(ThirdPartyLibs)

add_subdirectory(GLAD)
add_subdirectory(GLFW)

set(EXTRA_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/GLAD/build/include
                   ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include
    CACHE INTERNAL "")

find_library(GLFW_LIB glfw3 PATHS ${CMAKE_CURRENT_SOURCE_DIR}/GLFW/build/src)
find_library(COCOA_LIB Cocoa)
find_library(IOKIT_LIB IOKit)

set(EXTRA_LIBS ${GLFW_LIB} ${COCOA_LIB} ${IOKIT_LIB}
    CACHE INTERNAL "")
