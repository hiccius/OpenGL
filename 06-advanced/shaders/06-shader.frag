#version 410 core
uniform sampler2D screenTexture;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    fragColor = texture(screenTexture, textureCoordinates);
}
