#version 330 core

in vec4 in_Position;
in vec4 in_Normal;
in vec2 in_UV;
out vec4 ex_Color;
out vec2 ex_UV;

uniform vec4 Color;
uniform mat4 ModelMatrix;
layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};
layout(std140) uniform Light
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_Color = Color;
	ex_UV = in_UV;
}
