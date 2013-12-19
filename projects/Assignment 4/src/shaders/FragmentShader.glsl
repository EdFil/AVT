#version 330 core

in vec4 ex_Color;
in vec2 ex_UV;
out vec4 out_Color;

uniform sampler2D Texture;

void main(void)
{
	out_Color = texture(Texture, ex_UV) + ex_Color;
}

