#version 410 core
out vec4 fragColor;

void main()
{
    if (gl_FragCoord.x < 400)
    {
        fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else
    {
        fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
}
