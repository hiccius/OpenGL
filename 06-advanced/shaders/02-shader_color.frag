#version 410 core
uniform sampler2D diffuse;

in  vec2 textureCoordinates;
out vec4 fragColor;

float LinearizeDepth(float aDepth, float aNear, float aFar)
{
    float z = aDepth * 2.0f - 1.0f;
    return ((2.0f * aNear * aFar) / (aFar + aNear - z * (aFar - aNear))) / aFar;
}

void main()
{
    fragColor = vec4(0.04f, 0.28f, 0.26f, 1.0f);
}
