#version 410

layout(location = 0) out vec4 color;

uniform vec4 Colour;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main() 
{ 
	float intensity = 1.0 / length(fs_in.position.xy);
	color = fs_in.color * intensity;
}