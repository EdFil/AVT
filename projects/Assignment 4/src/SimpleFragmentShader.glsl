#version 330 core

in vec4 ex_Color;
in vec2 ex_UV;
out vec4 out_Color;

uniform sampler2D Texture;

void main(void)
{

	out_Color = texture(Texture, ex_UV);
	//out_Color = vec4(ex_UV, 0.0, 1.0);
	//out_Color = ex_Color;
}

