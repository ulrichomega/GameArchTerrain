#version 150

in vec3 color;;
uniform sampler2D s_tex;

out vec4 FragColor;

void main(void)
{
	FragColor = vec4(color,1.0);
}