#version 410 core
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;

in  vec3 normal;
in  vec3 fragPos;
out vec4 fragColor;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    float diffuseStrength = max(dot(normalize(normal), normalize(lightPosition - fragPos)), 0.0f);
    vec3 diffuse = diffuseStrength * lightColor;

    fragColor = vec4((ambient + diffuse) * objectColor, 1.0f);
}
