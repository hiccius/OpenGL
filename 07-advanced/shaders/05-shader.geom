#version 410 core
layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

in VsOut
{
    vec3 color;
} gsIn[];
out vec3 fColor;

void BuildHouse(vec4 centre)
{
    fColor = gsIn[0].color;
    gl_Position = centre + vec4(-0.2f, -0.2f, 0.0f, 0.0f); // bottom left
    EmitVertex();
    gl_Position = centre + vec4( 0.2f, -0.2f, 0.0f, 0.0f); // bottom right
    EmitVertex();
    gl_Position = centre + vec4(-0.2f,  0.2f, 0.0f, 0.0f); // top left
    EmitVertex();
    gl_Position = centre + vec4( 0.2f,  0.2f, 0.0f, 0.0f); // top right
    EmitVertex();
    gl_Position = centre + vec4( 0.0f,  0.4f, 0.0f, 0.0f); // top
    fColor = vec3(1.0f, 1.0f, 1.0f);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    BuildHouse(gl_in[0].gl_Position);
}
