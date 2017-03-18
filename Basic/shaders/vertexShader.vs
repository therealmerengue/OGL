#version 410
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	fColor = color;
}