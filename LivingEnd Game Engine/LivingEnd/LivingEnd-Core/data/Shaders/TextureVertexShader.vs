#version 410

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TexCoord;

uniform mat4 ProjectionView;

out vTexCoord;

void main()
{
	vTexCoord = TexCoord;
	gl_Position = ProjectionView * Position;
}