#version 410 core
uniform sampler2D screenTexture;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    fragColor = texture(screenTexture, textureCoordinates);
    float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
    fragColor = vec4(vec3(average), 1.0f);
}
