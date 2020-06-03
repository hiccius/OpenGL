#version 410 core
in vec2 textureCoordinate;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragColor;

void main()
{
    fragColor = mix(texture(texture1, textureCoordinate),
                    texture(texture2, vec2(1.0f - textureCoordinate.x, textureCoordinate.y)),
                    0.2f);
}
