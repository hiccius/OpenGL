cmake_minimum_required(VERSION 3.0)

project(Test)

set(CMAKE_CXX_STANDARD 17)

add_executable(11-Triangle main.cpp ${EXTRA_SOURCES})

target_include_directories(11-Triangle PRIVATE ${EXTRA_INCLUDES})
target_link_libraries(11-Triangle ${EXTRA_LIBS})

target_compile_options(11-Triangle PRIVATE -Wall -Wextra -pedantic-errors -Werror)
