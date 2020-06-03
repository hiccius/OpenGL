#version 410 core

in vec3 aPosVertex;

out vec4 fragColor;

void main()
{
    fragColor = vec4(aPosVertex, 1.0f);
}
