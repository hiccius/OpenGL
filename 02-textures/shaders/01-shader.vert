#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTextureCoordinate;

out vec3 color;
out vec2 textureCoordinate;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    color = aColor;
    textureCoordinate = aTextureCoordinate;
}
