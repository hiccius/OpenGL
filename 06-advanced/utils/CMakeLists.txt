cmake_minimum_required(VERSION 3.3)

project(OpenGLUtils VERSION 0.0.6 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils_06
    src/camera.cpp
    src/framebuffer.cpp
    src/matrix.cpp
    src/mesh.cpp
    src/model.cpp
    src/renderbufferobject.cpp
    src/shader.cpp
    src/shaderprogram.cpp
    src/texture.cpp
    src/vertexbufferobject.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils_06 PUBLIC OpenGLThirdParty)
target_include_directories(utils_06 PUBLIC include)
