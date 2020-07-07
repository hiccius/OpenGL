#version 410 core
uniform samplerCube skyboxTexture;
uniform vec3        cameraPosition;

in  vec3 normalVector;
in  vec3 position;
out vec4 fragColor;

void main()
{
    float refractiveRatio = 1.0f / 1.52f;
    vec3 incident = normalize(position - cameraPosition);
    vec3 refraction = refract(incident, normalize(normalVector), refractiveRatio);

    fragColor = vec4(texture(skyboxTexture, refraction).rgb, 1.0f);
}
