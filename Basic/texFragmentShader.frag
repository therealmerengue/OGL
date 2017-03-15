#version 410

in vec2 pass_textureCoords;

out vec4 out_color;

uniform sampler2D textureSampler;
uniform vec3 spriteColor;

void main()
{
	out_color = vec4(spriteColor, 1.0) * texture(textureSampler, pass_textureCoords);
}