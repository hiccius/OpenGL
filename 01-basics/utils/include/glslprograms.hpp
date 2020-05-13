#ifndef GLSLSPROGRAMS_HPP
#define GLSLSPROGRAMS_HPP

#include <string>


static constexpr std::string_view vertexShaderSource{
"#version 410 core"                                     "\n"
"layout(location = 0) in vec3 aPos;"                    "\n"
"void main()"                                           "\n"
"{"                                                     "\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"  "\n"
"}"};

static constexpr std::string_view fragmentShaderSource{
"#version 410 core"                             "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);"  "\n"
"}"};

/*
static constexpr std::string_view fragmentShaderSourceYellow =
"#version 440 core"                             "\n"
"out vec4 fragColor;"                           "\n"
"void main()"                                   "\n"
"{"                                             "\n"
    "fragColor = vec4(1.0f, 1.0f, 0.2f, 1.0);"  "\n"
"};";
*/
#endif // GLSLSPROGRAMS_HPP
