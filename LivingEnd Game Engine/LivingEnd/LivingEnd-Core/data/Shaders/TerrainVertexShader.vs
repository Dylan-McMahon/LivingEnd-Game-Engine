#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 ProjectionView;
uinform sampler2D Perlin_Texture

out vTexCoord;

void main()
{
	vec4 pos = Position;
	pos.y += texture(Perlin_Texture, TexCoord).r * 5;

	vTexCoord = TexCoord;
	gl_Position = ProjectionView * pos;
}