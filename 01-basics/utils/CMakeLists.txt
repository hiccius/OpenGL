cmake_minimum_required(VERSION 3.3)

project(OpenGLUtils VERSION 0.0.1 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils_01
    src/shader.cpp
    src/shaderprogram.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils_01 PUBLIC OpenGLThirdParty)
target_include_directories(utils_01 PUBLIC include)
