#version 150

in vec4 in_Position;
in vec2 in_Tex;

uniform float time;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec2 v_tex;

void main( void )
{
	// make sure the interpolation parameter is not negative.
	float beta = max( 0.0, sin( time ) );

	vec3 p = in_Position.xyz; 			 // original position
	vec3 n = normalize( in_Position.xyz ) * 5; // point on unit sphere

	// do linear interpolation
	vec3 v = n * beta + p * ( 1.0 - beta );

	// in case normalize fails...
	if( p == vec3( 0.0, 0.0, 0.0 ) )
	{
		v = p;
	}

	// continue the transformation.
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4( v, 1.0 );
	v_tex = in_Tex;
}
