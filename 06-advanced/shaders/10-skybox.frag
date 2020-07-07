#version 410 core
uniform samplerCube skyboxTexture;

in  vec3 textureCoordinates;
out vec4 fragColor;

void main()
{
    fragColor = texture(skyboxTexture, textureCoordinates);
}
