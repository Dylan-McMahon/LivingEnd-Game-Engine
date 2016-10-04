#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 ProjectionView_matrix;

out vec2 frag_TexCoord;

uniform sampler2D perlin_texture;

void main()
{
	vec4 pos = Position;
	pos.y += texture(perlin_texture, TexCoord).r * 5;

	frag_TexCoord = TexCoord;
	gl_Position = ProjectionView_matrix * pos;
}