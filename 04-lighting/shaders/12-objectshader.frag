#version 410 core
struct Material
{
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;
};

struct Light
{
    vec3    position;
    vec3    direction;
    float   cosCutOffAngle;
    float   cosOuterCutOffAngle;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constantAtt;
    float linearAtt;
    float quadraticAtt;
};

uniform Material    material;
uniform Light       light;
uniform vec3        viewPosition;

in  vec2 textureCoordinates;
in  vec3 normal;
in  vec3 fragPosition;
out vec4 fragColor;

void main()
{
    vec3 materialTexture = texture(material.diffuse, textureCoordinates).rgb;

    // ambient lighting
    vec3 ambient = materialTexture * light.ambient;

    // diffuse lighting
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diffuseIntensity = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = materialTexture * diffuseIntensity * light.diffuse;

    // specular lighting
    vec3 viewDirection = normalize(viewPosition - fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = texture(material.specular, textureCoordinates).rgb * specularIntensity * light.specular;

    // spotlight
    float cosFragmentAngle = dot(-lightDirection, normalize(light.direction));
    float intensity = clamp((cosFragmentAngle - light.cosOuterCutOffAngle) /
                            (light.cosCutOffAngle - light.cosOuterCutOffAngle), 0.0f, 1.0f);

    // attenuation
    float lightDistance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constantAtt + light.linearAtt * lightDistance +
                               light.quadraticAtt * lightDistance * lightDistance);

    // final value
    fragColor = vec4((ambient + (diffuse + specular) * intensity) * attenuation, 1.0f);
}
