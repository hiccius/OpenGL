#version 410 core
uniform vec3 objectColor;

in  vec3 lightingColor;
out vec4 fragColor;

void main()
{
    fragColor = vec4(lightingColor * objectColor, 1.0f);
}
