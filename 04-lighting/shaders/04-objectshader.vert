#version 410 core
uniform mat4 model;
uniform mat4 normalMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 lightingColor;

void main()
{
    vec3 position = vec3(model * vec4(aPos, 1.0f));
    vec3 normal = normalize(mat3(normalMatrix) * aNormal);
    gl_Position = projection * view * vec4(position, 1.0f);

    // ambient lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse lighting
    vec3 lightDirection = normalize(lightPosition - position);
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diffuseIntensity * lightColor;

    // specular lighting
    float specularStrength = 1.0f;
    vec3 viewDirection = normalize(viewPosition - position);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
    vec3 specular = specularStrength * specularIntensity * lightColor;

    lightingColor = ambient + diffuse + specular;
}
