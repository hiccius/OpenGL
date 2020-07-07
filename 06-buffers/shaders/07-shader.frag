#version 410 core
uniform sampler2D screenTexture;
uniform int       effect;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    if (effect == 1)
    {
        fragColor = vec4(vec3(1.0f - texture(screenTexture, textureCoordinates)), 1.0f);
    }
    else if (effect == 2)
    {
        fragColor = texture(screenTexture, textureCoordinates);
        float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
        fragColor = vec4(vec3(average), 1.0f);
    }
    else
    {
        fragColor = texture(screenTexture, textureCoordinates);
    }
}
