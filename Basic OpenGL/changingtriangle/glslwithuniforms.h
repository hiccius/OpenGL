#pragma once

#include "helpers.h"

constexpr CStringLiteral vertexShaderSource =
"#version 440 core"                                     "\n"
"layout(location = 0) in vec3 aPos;"                    "\n"
"void main()"                                           "\n"
"{"                                                     "\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"  "\n"
"};";

constexpr CStringLiteral fragmentShaderSourceOrange =
"#version 440 core"                             "\n"
"out vec4 fragColor;"                           "\n"
"uniform vec4 ourColor;"                        "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = ourColor;"                     "\n"
"};";