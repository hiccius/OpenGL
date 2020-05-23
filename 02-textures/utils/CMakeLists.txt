cmake_minimum_required(VERSION 3.0)

project(OpenGLUtils VERSION 0.0.2 LANGUAGES CXX)

set_property(SOURCE ${EXTRA_SOURCES}
             PROPERTY GENERATED TRUE)

add_library(utils_02
    src/shader.cpp
    src/shaderprogram.cpp
    src/texturehandler.cpp
    src/vertexdatahandler.cpp
    src/window.cpp
    ${EXTRA_SOURCES})

target_link_libraries(utils_02 PUBLIC OpenGLThirdParty)
target_include_directories(utils_02 PUBLIC include)
