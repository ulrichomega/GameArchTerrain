#version 150
//Base code from Professor Destefano

in vec4 in_Position;
in vec2 in_Tex;
//in vec3 in_Normal; Not using per-vertex normals, using normal maps

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 LightPosition;// = vec3(-3.0, 3.0, 3.0); 
uniform float constantAttenuation;// = 0.5;
uniform float linearAttenuation;// = 0.01;
uniform float quadraticAttenuation;// = 0.005;

out vec2 v_tex;
out vec3 VP;
out vec3 eyePos;
out float attenuation;

void main(void)
{
    //eye coordinate position
    vec3 ecPos = (ViewMatrix * ModelMatrix * in_Position).xyz;
    eyePos = -normalize(ecPos);
    
    //vector from surface to light position
    VP = vec3(LightPosition - ecPos);
    //distance from light to surface
    float d = length(VP);
    VP = normalize(VP);
    //compute attenuation
    attenuation = 1.0 / (constantAttenuation +
                        linearAttenuation * d +
                        quadraticAttenuation * d * d);
    
	gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * in_Position;
	v_tex = in_Tex;
}