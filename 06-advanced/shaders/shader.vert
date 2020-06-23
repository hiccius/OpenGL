#version 410 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTextureCoordinates;

out vec2 textureCoordinates;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    textureCoordinates = aTextureCoordinates;
}
