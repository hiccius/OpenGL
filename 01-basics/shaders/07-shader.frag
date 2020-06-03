#version 410 core

in vec3 ourColor;

out vec4 fragColor;

void main()
{
    fragColor = vec4(ourColor, 1.0f);
}
