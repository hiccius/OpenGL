#version 410 core
uniform mat4 modelView;
uniform mat4 normalMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 worldLightPos;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 fragPosition;
out vec3 lightPosition;
out vec3 normal;

void main()
{
    fragPosition = vec3(modelView * vec4(aPos, 1.0f));
    lightPosition = vec3(view * vec4(worldLightPos, 1.0f));
    normal = normalize(mat3(normalMatrix) * aNormal);
    gl_Position = projection * vec4(fragPosition, 1.0f);
}
