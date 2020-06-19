cmake_minimum_required(VERSION 3.0)

project(examples)

add_executable(main main.cpp mesh.cpp model.cpp)
target_link_libraries(main PRIVATE utils_05)
