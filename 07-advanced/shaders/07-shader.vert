#version 410 core
layout(std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec2 aTextureCoordinates;

out vec2 textureCoordinates;

void main()
{
    gl_Position = projection * view * model * vec4(aPosition, 1.0f);
    textureCoordinates = aTextureCoordinates;
}
