#version 410 core
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 fragColor;

void main()
{
    fragColor = vec4(lightColor * objectColor, 1.0f);
}
