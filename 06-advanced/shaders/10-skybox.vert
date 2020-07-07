#version 410 core
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 aPos;

out vec3 textureCoordinates;

void main()
{
    textureCoordinates = aPos;
    vec4 position = projection * mat4(mat3(view)) * vec4(aPos, 1.0f);
    gl_Position = position.xyww;
}
