#version 410 core

out vec4 fragColor;

in vec4 vertexColor;

void main()
{
    fragColor = vertexColor;
}
