#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 ProjectionView;

out vec2 frag_TexCoord;

void main()
{
	frag_texCoord = TexCoord;
	gl_position = ProjectionView * Position;
}