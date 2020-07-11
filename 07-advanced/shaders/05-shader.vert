#version 410 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out VsOut
{
    vec3 color;
} vsOut;

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0f);
    vsOut.color = aColor;
}
