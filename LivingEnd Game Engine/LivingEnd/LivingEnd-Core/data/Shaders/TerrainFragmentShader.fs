#version 410

in vec2 frag_TexCoord;
in float frag_Height;

out vec4 FragColor;
uniform sampler2D perlin_texture;
uniform float SeaLevel;

void main()
{
	//Assign fragcolour to different values depending on height
	if (frag_Height >= SeaLevel )
	{
		FragColor = normalize(vec4(0, 153, 76, 1));
	}
	else
	{
		FragColor = normalize(vec4(0, 0, 204, 1));
	}
	//FragColor = texture(perlin_texture, frag_TexCoord).rrrr;
	FragColor.a = 1;
}