#version 410 core
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

in  vec3 normal;
in  vec3 fragPosition;
out vec4 fragColor;

void main()
{
    // ambient lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse lighting
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diffuseIntensity * lightColor;

    // specular lighting
    float specularStrength = 0.5f;
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
    vec3 specular = specularStrength * specularIntensity * lightColor;

    fragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}
