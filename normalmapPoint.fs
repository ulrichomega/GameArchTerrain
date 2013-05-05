#version 150
//Code based on http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/

in vec2 UV;
in vec3 Position_worldSpace;

in vec3 LightDirection_tanSpace;
in vec3 VertexDirection_tanSpace;

uniform sampler2D s_tex;
uniform sampler2D s_normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform float LightBrightness;

uniform vec3 ambient;// = vec3(.05, 0.05, 0.05);
uniform vec3 diffuse;// = vec3(0.9, 0.5, 0.5);
uniform vec3 specular;// = vec3(0.7, 0.7, 0.7);

out vec4 FragColor;

void main(void)
{
	vec3 diffuseColor = texture2D( s_tex, UV ).rgb;
	vec3 ambientColor = ambient * diffuseColor;
	vec3 specularColor = specular;

    vec3 TextureNormal_tanSpace = normalize(texture2D( s_normal, vec2(UV.x,-UV.y) ).rgb*2.0 - 1.0);
	
    float distance = length(LightPosition - Position_worldSpace);

    vec3 n = TextureNormal_tanSpace;
    vec3 l = normalize (LightDirection_tanSpace);
    float cosTheta = clamp( dot( n,l), 0,1);

    vec3 E = normalize(VertexDirection_tanSpace);
    vec3 R = reflect(-l,n);

    float cosAlpha = clamp(dot(E,R), 0,1);

    FragColor = vec4((ambientColor
     + diffuseColor * LightColor * LightBrightness * cosTheta / (distance*distance)
     + specularColor * LightColor * LightBrightness * pow(cosAlpha,5) / (distance*distance)),1);

}