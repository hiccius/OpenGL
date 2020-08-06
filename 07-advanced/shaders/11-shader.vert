#version 410 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 aPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
}
