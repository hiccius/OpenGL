#version 410 core
uniform sampler2D diffuse;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    fragColor = texture(diffuse, textureCoordinates);
    if (fragColor.a < 0.1)
    {
        discard;
    }
}
