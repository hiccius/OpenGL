#version 410 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMatrix;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 normalVector;
out vec3 position;

void main()
{
    normalVector = mat3(normalMatrix) * aNormal;
    position = vec3(model * vec4(aPos, 1.0f));
    gl_Position = projection * view * vec4(position, 1.0f);
}
