#version 410
layout(location=0) in vec4 Position;
layout(location=1) in vec4 color;

uniform mat4 projection_matrix;
uniform mat4 view_matrix = mat4(1.0);
uniform mat4 model_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
} vs_out;

void main() 
{
	gl_Position = projection_matrix * view_matrix * model_matrix * Position; 
	vs_out.position = model_matrix * Position;
	vs_out.color = color;
}