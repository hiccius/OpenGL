cmake_minimum_required(VERSION 3.3)

project(OpenGLUtils VERSION 0.0.8 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils_08
    src/camera.cpp
    src/cubemap.cpp
    src/drawable.cpp
    src/framebuffer.cpp
    src/matrix.cpp
    src/mesh.cpp
    src/model.cpp
    src/renderbufferobject.cpp
    src/shader.cpp
    src/shaderprogram.cpp
    src/texture.cpp
    src/uniformbufferobject.cpp
    src/vertexbufferobject.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils_08 PUBLIC OpenGLThirdParty)
target_include_directories(utils_08 PUBLIC include)
