#version 150

in vec3 in_Position;
in vec3 in_Normal;
in vec3 in_Color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 color;

void main(void)
{
	gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vec4(in_Position,1);
	color = in_Color;
}