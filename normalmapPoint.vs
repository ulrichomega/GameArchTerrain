#version 150
//Code based on http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/

in vec3 in_Position;
in vec2 in_Tex;
in vec3 in_Normal; //Not using per-vertex normals, using normal maps
in vec3 in_Tangent;
in vec3 in_Bitangent;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec3 LightPosition;

out vec2 UV;
out vec3 Position_worldSpace;

out vec3 LightDirection_tanSpace;
out vec3 VertexDirection_tanSpace;

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(in_Position,1.0);

	Position_worldSpace = (ModelMatrix * vec4(in_Position, 1.0)).xyz;

	vec3 vertexPos_viewSpace = (ViewMatrix * ModelMatrix * vec4(in_Position, 1.0)).xyz;
	vec3 VertexDirection_viewSpace = vec3(0.0,0.0,0.0) - vertexPos_viewSpace;

	vec3 LightPos_viewSpace = (ViewMatrix * vec4(LightPosition, 1.0)).xyz;
	vec3 LightDirection_viewSpace = LightPos_viewSpace + VertexDirection_viewSpace;

	UV = in_Tex;
	
	mat3 MV3x3 = mat3(ViewMatrix * ModelMatrix);	//Translates from modelSpace to viewSpace
	vec3 vertexTangent_viewSpace = MV3x3 * in_Tangent;
	vec3 vertexBitangent_viewSpace = MV3x3 * in_Bitangent;
	vec3 vertexNormal_viewSpace = MV3x3 * in_Normal;

	mat3 TBN = transpose(mat3(
		vertexTangent_viewSpace,
		vertexBitangent_viewSpace,
		vertexNormal_viewSpace	
	));

	LightDirection_tanSpace = TBN * LightDirection_viewSpace;
	VertexDirection_tanSpace = TBN * VertexDirection_viewSpace;
}