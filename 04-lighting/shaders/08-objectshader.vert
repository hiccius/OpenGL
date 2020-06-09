#version 410 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextureCoordinates;

out vec3 normal;
out vec3 fragPosition;
out vec2 textureCoordinates;

void main()
{
    fragPosition = vec3(model * vec4(aPosition, 1.0f));
    gl_Position = projection * view * vec4(fragPosition, 1.0f);
    normal = normalize(aNormal);
    textureCoordinates = aTextureCoordinates;
}
