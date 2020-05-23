#version 410 core

in vec3 color;
in vec2 textureCoordinate;

uniform sampler2D textureSampler;

out vec4 fragColor;

void main()
{
	fragColor = texture(textureSampler, textureCoordinate) * vec4(color, 1.0f);
}
