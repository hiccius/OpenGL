#version 410 core
uniform sampler2D frontTexture;
uniform sampler2D backTexture;

in  VsOut
{
    vec2 textureCoordinates;
} fsIn;
out vec4 fragColor;

void main()
{
    if (gl_FrontFacing)
    {
        fragColor = texture(frontTexture, fsIn.textureCoordinates);
    }
    else
    {
        fragColor = texture(backTexture, fsIn.textureCoordinates);
    }
}
