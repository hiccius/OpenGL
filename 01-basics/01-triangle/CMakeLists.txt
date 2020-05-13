cmake_minimum_required(VERSION 3.0)

project(01-triangle)

add_executable(triangle main.cpp)

target_include_directories(triangle PRIVATE ${EXTRA_INCLUDES})
target_link_libraries(triangle ${EXTRA_LIBS})
