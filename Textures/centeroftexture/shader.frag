#version 440 core
in vec3 ourColor;
in vec2 textureCoord;

out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    fragColor = texture(texture1, textureCoord);
}