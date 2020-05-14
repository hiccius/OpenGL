cmake_minimum_required(VERSION 3.0)

project(OpenGLUtils VERSION 0.0.1 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils
    src/shader.cpp
    src/shaderprogram.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils PUBLIC OpenGLThirdParty)
target_include_directories(utils PUBLIC include)
target_compile_options(utils PRIVATE -Wall -Wextra -pedantic-errors -Werror)
