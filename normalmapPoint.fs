#version 150
//Base code from Professor Destefano

in vec2 v_tex;
//in float nDotVP;
in vec3 VP;
//in float pf;
in float attenuation;
in vec3 eyePos;

uniform mat3 NormalMatrix;

uniform sampler2D s_tex;
uniform sampler2D s_normal;

out vec4 FragColor;

uniform vec3 ambient = vec3(.05, 0.05, 0.05);
uniform vec3 diffuse = vec3(0.9, 0.5, 0.5);
uniform vec3 specular = vec3(0.7, 0.7, 0.7);
uniform float shininess;// = 50; //can be as high as 128 - bigger number = more concentrated bright spot

void main(void)
{
    vec3 tnorm = normalize(NormalMatrix * texture(s_normal,v_tex).rgb * 2.0 - 1.0f);
    float nDotVP = max(0.0, dot(tnorm, VP));
    vec3 HV = normalize(VP + eyePos);
    float nDotHV = max(0.0, dot(tnorm, HV));
    
    float pf;
    if (nDotVP == 0.0)
        pf = 0.0;
    else
        pf = pow(nDotHV, shininess);

	FragColor = texture(s_tex, v_tex) * vec4((ambient * attenuation + diffuse*nDotVP * attenuation + specular * pf * attenuation), 1);
    FragColor = texture(s_normal,v_tex) * 2.0 - 1.0;
}