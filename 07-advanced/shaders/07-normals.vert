#version 410 core
uniform mat4 normalMatrix;
layout(std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

out VsOut
{
    vec3 normal;
} vsOut;

void main()
{
    gl_Position = view * model * vec4(aPosition, 1.0f);
    vsOut.normal = normalize(mat3(normalMatrix) * aNormal);
}
