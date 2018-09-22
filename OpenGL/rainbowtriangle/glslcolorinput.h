#pragma once

#include "helpers.h"


constexpr CStringLiteral vertexShaderSource =
"#version 440 core"                                             "\n"
"layout(location = 0) in vec3 aPos;"                            "\n"
"layout(location = 1) in vec3 aColor;"                          "\n"
"uniform float offset;"                                         "\n"
"out vec3 ourColor;"                                            "\n"
"void main()"                                                   "\n"
"{"                                                             "\n"
    "gl_Position = vec4(aPos.x + offset, aPos.y, aPos.z, 1.0);" "\n"
    "ourColor = aPos;"                                          "\n"
"};";

constexpr CStringLiteral fragmentShaderSource =
"#version 440 core"                             "\n"
"in vec3 ourColor;"                             "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = vec4(ourColor, 1.0);"          "\n"
"};";
