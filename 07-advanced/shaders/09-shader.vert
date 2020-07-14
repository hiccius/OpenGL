#version 410 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aOffset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fColor;

void main()
{
    vec2 postion = aPosition * gl_InstanceID / 100.0f;
    gl_Position = projection * view * model * vec4(postion + aOffset, 0.0f, 1.0f);
    fColor = aColor;
}
