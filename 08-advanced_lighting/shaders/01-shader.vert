#version 410 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextureCoordinates;

out VsOut
{
    vec3 fragPosition;
    vec3 normal;
    vec2 textureCoordinates;
} vsOut;

void main()
{
    vsOut.fragPosition = aPos;
    vsOut.normal = aNormal;
    vsOut.textureCoordinates = aTextureCoordinates;

    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}
