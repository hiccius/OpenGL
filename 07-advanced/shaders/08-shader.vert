#version 410 core
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 offsets[100];

out vec3 fColor;

void main()
{
    vec2 offset = offsets[gl_InstanceID];
    gl_Position = projection * view * model * vec4(aPosition + offset, 0.0f, 1.0f);
    fColor = aColor;
}
