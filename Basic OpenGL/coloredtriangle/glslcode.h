#pragma once

#include "helpers.h"

constexpr CStringLiteral vertexShaderSource =
"#version 440 core"                                     "\n"
"layout(location = 0) in vec3 aPos;"                    "\n"
"out vec4 vertexColor;"                                 "\n"
"void main()"                                           "\n"
"{"                                                     "\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"  "\n"
    "vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"           "\n"
"};";

constexpr CStringLiteral fragmentShaderSourceOrange =
"#version 440 core"                             "\n"
"in  vec4 vertexColor;"                         "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = vertexColor;"                  "\n"
"};";