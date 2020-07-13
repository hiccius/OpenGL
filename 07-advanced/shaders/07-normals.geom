#version 410 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

layout(std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

in VsOut
{
    vec3 normal;
} gsIn[];

void GenerateLine(int aIndex)
{
    const float magnitude = 0.4f;
    gl_Position = projection *  gl_in[aIndex].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[aIndex].gl_Position +
                                magnitude * vec4(gsIn[aIndex].normal, 0.0f));
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0);
    GenerateLine(1);
    GenerateLine(2);
}
