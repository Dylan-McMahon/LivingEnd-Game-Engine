#version 410

in vec2 frag_TexCoord;

out vec4 FragColor;
uniform sampler2D perlin_texture;

void main()
{
	FragColor = texture(perlin_texture, frag_TexCoord).rrrr;
	FragColor.a = 1;
}