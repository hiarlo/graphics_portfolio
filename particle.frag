#version 440

uniform mat4 u_viewMatrix, u_projMatrix, u_modelMatrix, u_scalingMatrix;
uniform vec4 u_ambient;
uniform vec4 u_diffuse;
uniform vec4 u_specular;
uniform float u_shininess;
uniform vec4 u_lightPosition;
uniform vec4 u_attenuations;
uniform sampler2D s_texture;
uniform int  u_Tex;

uniform vec4 u_ecPosition;
uniform float u_randNum;

in vec4 v_position;
in vec4 v_color;
in vec4 v_normal;
in vec4 v_lightPosition;
in vec4 v_lightDirection;
in float v_lightDistance;
in vec2 v_texCoord;

out vec4 outputF;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 temp_color;

	vec4 lN = normalize(v_normal);

	vec4 L = normalize(v_lightPosition - v_position);
	vec4 V = normalize(-v_position);
	vec4 R = normalize(reflect(-L,lN));

	float att = clamp(
	1.0/(
		u_attenuations.x + 
		(u_attenuations.y * v_lightDistance) + 
		(u_attenuations.z * v_lightDistance * v_lightDistance)
		),
	0.0f, 
	1.0f);

	ambient = v_color * u_ambient;
	diffuse = v_color * u_diffuse * max(dot(lN, L), 0.0);
	specular = v_color * u_specular * pow(max(dot(R,V), 0.0), u_shininess);
	
/*
	//float v_ecDistance = distance(shadow_position, u_ecPosition) * 0.24;
	//float v_ecDistance = distance(u_ecPosition, shadow_position) * 0.24;
	
	float v_alpha = 1.0 - (v_ecDistance * v_ecDistance * v_ecDistance * 1.4);
	//float v_alpha = (1.0 - v_ecDistance) * 0.08;
	float v_random = rand(v_texCoord);

	temp_color = (att) * (ambient + diffuse + specular);
	
	if(u_Tex == 1)
	{
		outputF = temp_color;
	}
	else if(u_Tex ==2)
	{
		outputF = texture(s_texture, v_texCoord);// * vec4(0.32f, 0.32f, 0.32f, 0.1f);
	}
	else if(u_Tex == 0)
	{
		
		temp_color.a = mix(0.02, 0.8, v_alpha + (v_random * v_random));
		outputF = temp_color;
	}
*/

	//MAIN_DEBUG_SCENE1	
	//outputF = vec4(temp_color.a);
	//MAIN_DEBUG_SCENE2
	//outputF = vec4(1.0 - v_ecDistance);
	outputF = ambient + diffuse + specular;
	//outputF =  v_lightPosition;
	//outputF = vec4(1.0f, att, 0.0f, 1.0f);
}

