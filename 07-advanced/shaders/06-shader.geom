#version 410 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform float time;

in VsOut
{
    vec2 textureCoordinates;
} gsIn[];
out vec2 textureCoordinates;

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 move(vec4 aPosition, vec3 aNormal)
{
    float magnitude = 2.0f;
    vec3 movement = aNormal * magnitude * (sin(time) + 1.0f) / 2.0f;
    return aPosition + vec4(movement, 0.0f);
}

void main()
{
    vec3 normal = GetNormal();

    textureCoordinates = gsIn[0].textureCoordinates;
    gl_Position = move(gl_in[0].gl_Position, normal);
    EmitVertex();
    textureCoordinates = gsIn[1].textureCoordinates;
    gl_Position = move(gl_in[1].gl_Position, normal);
    EmitVertex();
    textureCoordinates = gsIn[2].textureCoordinates;
    gl_Position = move(gl_in[2].gl_Position, normal);
    EmitVertex();
    EndPrimitive();
}
