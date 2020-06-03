#version 410 core
in vec2 textureCoordinate;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float     weight;

out vec4 fragColor;

void main()
{
    fragColor = mix(texture(texture1, textureCoordinate),
                    texture(texture2, textureCoordinate),
                    weight);
}
