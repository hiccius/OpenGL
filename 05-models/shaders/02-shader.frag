#version 410 core
struct Material
{
    sampler2D   diffuse1;
    sampler2D   specular1;
    float       shininess;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constantAtt;
    float linearAtt;
    float quadraticAtt;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3    position;
    vec3    direction;
    float   cosCutOffAngle;
    float   cosOuterCutOffAngle;

    float constantAtt;
    float linearAtt;
    float quadraticAtt;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material            material;
uniform DirectionalLight    directionalLight;
uniform PointLight          pointLight;
uniform SpotLight           spotLight;
uniform vec3                viewPosition;

in  vec2 textureCoordinates;
in  vec3 normal;
in  vec3 fragPosition;
out vec4 fragColor;

vec3 CalculateDirectionalLight(DirectionalLight aLight, vec3 aNormal, vec3 aViewDirection);
vec3 CalculatePointLight(PointLight aLight, vec3 aNormal, vec3 aFragPosition, vec3 aViewDirection);
vec3 CalculateSpotLight(SpotLight aLight, vec3 aNormal, vec3 aFragPosition, vec3 aViewDirection);

void main()
{
    vec3 materialTexture = texture(material.diffuse1, textureCoordinates).rgb;
    vec3 viewDirection = normalize(viewPosition - fragPosition);

    vec3 light = CalculateDirectionalLight(directionalLight, normal, viewDirection);
    light += CalculatePointLight(pointLight, normal, fragPosition, viewDirection);
    light += CalculateSpotLight(spotLight, normal, fragPosition, viewDirection);

    fragColor = vec4(light * materialTexture, 1.0f);
}

vec3 CalculateDirectionalLight(DirectionalLight aLight, vec3 aNormal, vec3 aViewDirection)
{
    vec3 lightDirection = normalize(-aLight.direction);
    // ambient lighting
    vec3 ambient = aLight.ambient;
    // diffuse lighting
    float diffuseIntensity = max(dot(aNormal, lightDirection), 0.0f);
    vec3 diffuse = diffuseIntensity * aLight.diffuse;
    // specular lighting
    vec3 reflectDirection = reflect(-lightDirection, aNormal);
    float specularIntensity = pow(max(dot(aViewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = specularIntensity * aLight.specular;
    // combine all
    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight aLight, vec3 aNormal, vec3 aFragPosition, vec3 aViewDirection)
{
    vec3 lightDirection = normalize(aLight.position - aFragPosition);
    // ambient lighting
    vec3 ambient = aLight.ambient;
    // diffuse lighting
    float diffuseIntensity = max(dot(aNormal, lightDirection), 0.0f);
    vec3 diffuse = diffuseIntensity * aLight.diffuse;
    // specular lighting
    vec3 reflectDirection = reflect(-lightDirection, aNormal);
    float specularIntensity = pow(max(dot(aViewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = specularIntensity * aLight.specular;
    // attenuation
    float lightDistance = length(aLight.position - aFragPosition);
    float attenuation = 1.0 / (aLight.constantAtt + aLight.linearAtt * lightDistance +
                               aLight.quadraticAtt * lightDistance * lightDistance);
    // combine all
    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight(SpotLight aLight, vec3 aNormal, vec3 aFragPosition, vec3 aViewDirection)
{
    vec3 lightDirection = normalize(aLight.position - aFragPosition);
    // ambient lighting
    vec3 ambient = aLight.ambient;
    // diffuse lighting
    float diffuseIntensity = max(dot(aNormal, lightDirection), 0.0f);
    vec3 diffuse = diffuseIntensity * aLight.diffuse;
    // specular lighting
    vec3 reflectDirection = reflect(-lightDirection, aNormal);
    float specularIntensity = pow(max(dot(aViewDirection, reflectDirection), 0.0f), material.shininess);
    vec3 specular = specularIntensity * aLight.specular;
    // spotlight
    float cosFragmentAngle = dot(-lightDirection, normalize(aLight.direction));
    float intensity = clamp((cosFragmentAngle - aLight.cosOuterCutOffAngle) /
                            (aLight.cosCutOffAngle - aLight.cosOuterCutOffAngle), 0.0f, 1.0f);
    // attenuation
    float lightDistance = length(aLight.position - fragPosition);
    float attenuation = 1.0f / (aLight.constantAtt + aLight.linearAtt * lightDistance +
                                aLight.quadraticAtt * lightDistance * lightDistance);
    // combine all
    return (ambient + diffuse + specular) * intensity * attenuation;
}
