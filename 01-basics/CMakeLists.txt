cmake_minimum_required(VERSION 3.0)

project(01-basics)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(utils)
set(EXTRA_INCLUDES ${EXTRA_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/utils/include)
set(EXTRA_LIBS ${EXTRA_LIBS} utils)

add_subdirectory(01-triangle)
