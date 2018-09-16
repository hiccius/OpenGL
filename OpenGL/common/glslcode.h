#pragma once

#include "helpers.h"


constexpr CStringLiteral vertexShaderSource =
"#version 440 core"                                     "\n"
"layout(location = 0) in vec3 aPos;"                    "\n"
"void main()"                                           "\n"
"{"                                                     "\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"  "\n"
"};";

constexpr CStringLiteral fragmentShaderSource =
"#version 440 core"                             "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);"  "\n"
"};";