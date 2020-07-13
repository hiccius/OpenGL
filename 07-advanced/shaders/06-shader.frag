#version 410 core
struct Material
{
    sampler2D diffuse1;
    sampler2D specular1;
};

uniform Material material;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    fragColor = texture(material.diffuse1, textureCoordinates);
}
