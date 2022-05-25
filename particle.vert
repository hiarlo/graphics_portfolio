#version 430

uniform mat4 u_viewMatrix, u_projMatrix;
uniform vec4 u_lightPosition;

in vec4 a_position;
in vec4 a_color;
in vec4 a_normal;
in vec4 a_texcoord;

out vec4 v_position;
out vec4 v_color;
out vec4 v_normal;
out vec4 v_texcoord;

out vec4 v_lightPosition;
out vec4 v_lightDirection;
out float v_lightDistance;

//Shadow Matrix(S) must be constructed on Shader level
//which calculates t with normal vector(n), LightPosition(A), LightDirection(L).

void main()
{
	v_position = u_viewMatrix * a_position;
	v_color = a_color;
	
	v_normal = normalize(u_viewMatrix * a_normal);
	v_lightPosition = u_viewMatrix * u_lightPosition;
	//dakuwaqa : lightPosition as it is!
	v_lightPosition = u_lightPosition; 
	v_lightDirection = v_position - v_lightPosition;
	v_lightDistance = length(v_lightDirection);

	//gl_PointSize = 3.0f;
	gl_Position = u_projMatrix * u_viewMatrix * a_position;
	
}

// make projection matrix in vertex shader 
// project vertex P onto the (Shadow receiver - plane)
