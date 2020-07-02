#version 410 core
uniform sampler2D screenTexture;
uniform int       effect;

in  vec2 textureCoordinates;
out vec4 fragColor;

void main()
{
    const float offset = 1.0 / 300.0;
    vec2 offsets[] = vec2[](
        vec2(-offset, offset),  vec2(0.0, offset),  vec2(offset, offset),
        vec2(-offset, 0.0),     vec2(0.0, 0.0),     vec2(offset, 0.0),
        vec2(-offset, -offset), vec2(0.0, -offset), vec2(offset, -offset)
    );

    float kernel[9];
    if (effect == 1)
    {
        kernel = float[](
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1
        );
    }
    else if (effect == 2)
    {
        kernel = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
        );
    }
    else if (effect == 3)
    {
        kernel = float[](
            1,  1, 1,
            1, -8, 1,
            1,  1, 1
        );
    }
    else
    {
        fragColor = texture(screenTexture, textureCoordinates);
        return;
    }

    fragColor = vec4(vec3(0.0), 1.0f);
    for (int i = 0; i < kernel.length(); ++i)
    {
        fragColor.rgb += texture(screenTexture, textureCoordinates.st + offsets[i]).rgb * kernel[i];
    }
}
