#version 330 core

in vec4 in_Position;
in vec2 in_UV;
out vec4 ex_Color;
out vec2 ex_UV;

uniform vec4 Color;

void main(void)
{
	gl_Position = in_Position;
	ex_Color = vec4(Color.rgb + 0.3,1.0);
	ex_UV = in_UV;
}