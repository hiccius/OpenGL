#version 410 core
uniform sampler2D diffuse;
uniform bool      viewDepth;

in  vec2 textureCoordinates;
out vec4 fragColor;

float LinearizeDepth(float aDepth, float aNear, float aFar)
{
    float z = aDepth * 2.0f - 1.0f;
    return ((2.0f * aNear * aFar) / (aFar + aNear - z * (aFar - aNear))) / aFar;
}

void main()
{
    if(viewDepth)
    {
        float depth = LinearizeDepth(gl_FragCoord.z, 0.1f, 100.0f);
        fragColor = vec4(vec3(depth), 1.0f);
    }
    else
    {
        fragColor = texture(diffuse, textureCoordinates);
    }
}
