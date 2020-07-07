#version 410 core
uniform samplerCube skyboxTexture;
uniform vec3        cameraPosition;

in  vec3 normalVector;
in  vec3 position;
out vec4 fragColor;

void main()
{
    vec3 incident = normalize(position - cameraPosition);
    vec3 reflection = reflect(incident, normalize(normalVector));

    fragColor = vec4(texture(skyboxTexture, reflection).rgb, 1.0f);
}
