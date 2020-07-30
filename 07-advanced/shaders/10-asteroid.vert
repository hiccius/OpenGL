#version 410 core
layout (std140) uniform Matrices
{
    mat4 view;
    mat4 projection;
};

layout(location = 0) in vec3 aPosition;
layout(location = 2) in vec2 aTextureCoordinates;
layout(location = 3) in mat4 aInstanceModel;

out vec2 textureCoordinates;

void main()
{
    textureCoordinates = aTextureCoordinates;
    gl_Position = projection * view * aInstanceModel * vec4(aPosition, 1.0f);
}
