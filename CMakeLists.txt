cmake_minimum_required(VERSION 3.0)

project(OpenGL)

set(CMAKE_CXX_STANDARD 17)
if(APPLE)
    set(COMPILER_OPTIONS "-Wall -Wextra -pedantic-errors -Werror")
elseif(WIN32)
    set(COMPILER_OPTIONS "-W4")
endif()

add_subdirectory(third-party)
add_subdirectory(01-basics)
