cmake_minimum_required(VERSION 3.0)

project(OpenGLUtils VERSION 0.0.3 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils_03
    src/camera.cpp
    src/matrix.cpp
    src/shader.cpp
    src/shaderprogram.cpp
    src/texture.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils_03 PUBLIC OpenGLThirdParty)
target_include_directories(utils_03 PUBLIC include)
