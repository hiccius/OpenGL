#version 410 core
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light    light;
uniform vec3     viewPosition;

in  vec3 normal;
in  vec3 fragPosition;
out vec4 fragColor;

void main()
{
    // ambient lighting
    vec3 ambient = material.ambient * light.ambient;

    // diffuse lighting
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = material.diffuse * diffuseIntensity * light.diffuse;

    // specular lighting
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = material.specular * specularIntensity * light.specular;

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}
