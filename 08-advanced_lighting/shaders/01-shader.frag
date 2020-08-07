#version 410 core
struct Light
{
    vec3 position;

    float ambient;
    float diffuse;
    float specular;
};

uniform sampler2D   diffuse;
uniform Light       light;
uniform vec3        viewPosition;

in VsOut
{
    vec3 fragPosition;
    vec3 normal;
    vec2 textureCoordinates;
} fsIn;
out vec4    fragColor;

void main()
{
    vec3 materialTexture = texture(diffuse, fsIn.textureCoordinates).rgb;

    // ambient lighting
    vec3 ambient = materialTexture * light.ambient;

    // diffuse lighting
    vec3 lightDirection = normalize(light.position - fsIn.fragPosition);
    float diffuseIntensity = max(dot(fsIn.normal, lightDirection), 0.0f);
    vec3 diffuse = materialTexture * diffuseIntensity * light.diffuse;

    // specular lighting
    vec3 viewDirection = normalize(viewPosition - fsIn.fragPosition);
    vec3 reflectDirection = reflect(-lightDirection, fsIn.normal);
    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0f), 0.5f);
    vec3 specular = specularIntensity * vec3(light.specular);

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}
