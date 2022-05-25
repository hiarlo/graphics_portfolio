 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>   //  To use functions with variables arguments
#include <memory.h>
#include <math.h>
#include <GL/glew.h>
#include <glut.h>
#include <glm\glm.hpp>

#include "textfile.h"

using namespace std;

#include "SOIL.h"
#include <vector>
 
#define M_PI       3.14159265358979323846

/********************************************************************

						GEOIMETRY SHADER EXAMPLE

*********************************************************************/
float points[] = {
	-0.45f, 0.45f, 0.0f, 1.0f,	//POSITIONS
	0.45f, 0.45f, 0.0f, 1.0f,
	0.45f, -0.45f, 0.0f, 1.0f,
	-0.45f, -0.45f, 0.0f, 1.0f
};

float colors[] = {
	1.0f, 0.0f, 0.0f, 1.0f, //RED
	0.0f, 1.0f, 0.0f, 1.0f, //GREEN
	.0f, 0.0f, 1.0f, 1.0f,  //BLUE
	1.0f, 1.0f, 1.0f, 1.0f  //WHITE
};
float verticesAxis[] = {-20.0f, 0.0f, 0.0f, 1.0f,
            20.0f, 0.0f, 0.0f, 1.0f,
 
            0.0f, -20.0f, 0.0f, 1.0f,
            0.0f,  20.0f, 0.0f, 1.0f,
 
            0.0f, 0.0f, -20.0f, 1.0f,
            0.0f, 0.0f,  20.0f, 1.0f};
 
float colorAxis[] = { 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f };


/********************************************************************/

GLfloat verticesCube[] = {
	// Positions         
	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,

	-1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,

	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,

	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f
};

float colorsCube[] = {
	0.583f, 0.771f, 0.014f, 1.0f,
	0.609f, 0.115f, 0.436f, 1.0f,
	0.327f, 0.483f, 0.844f, 1.0f,
	0.822f, 0.569f, 0.201f, 1.0f,
	0.435f, 0.602f, 0.223f, 1.0f,
	0.310f, 0.747f, 0.185f, 1.0f,
	0.597f, 0.770f, 0.761f, 1.0f,
	0.559f, 0.436f, 0.730f, 1.0f,
	0.359f, 0.583f, 0.152f, 1.0f,
	0.483f, 0.596f, 0.789f, 1.0f,
	0.559f, 0.861f, 0.639f, 1.0f,
	0.195f, 0.548f, 0.859f, 1.0f,
	0.014f, 0.184f, 0.576f, 1.0f,
	0.771f, 0.328f, 0.970f, 1.0f,
	0.406f, 0.615f, 0.116f, 1.0f,
	0.676f, 0.977f, 0.133f, 1.0f,
	0.971f, 0.572f, 0.833f, 1.0f,
	0.140f, 0.616f, 0.489f, 1.0f,
	0.997f, 0.513f, 0.064f, 1.0f,
	0.945f, 0.719f, 0.592f, 1.0f,
	0.543f, 0.021f, 0.978f, 1.0f,
	0.279f, 0.317f, 0.505f, 1.0f,
	0.167f, 0.620f, 0.077f, 1.0f,
	0.347f, 0.857f, 0.137f, 1.0f,
	0.055f, 0.953f, 0.042f, 1.0f,
	0.714f, 0.505f, 0.345f, 1.0f,
	0.783f, 0.290f, 0.734f, 1.0f,
	0.722f, 0.645f, 0.174f, 1.0f,
	0.302f, 0.455f, 0.848f, 1.0f,
	0.225f, 0.587f, 0.040f, 1.0f,
	0.517f, 0.713f, 0.338f, 1.0f,
	0.053f, 0.959f, 0.120f, 1.0f,
	0.393f, 0.621f, 0.362f, 1.0f,
	0.673f, 0.211f, 0.457f, 1.0f,
	0.820f, 0.883f, 0.371f, 1.0f,
	0.982f, 0.099f, 0.879f, 1.0f
};

GLfloat normalsCube[] = {
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,

	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,

	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f
};

/********************************************************************/

//Data for plane
float verticesPlane[] = { -40.0f, -10.0f, -40.0f, 1.0f,
-40.0f, -10.0f, 40.0f, 1.0f,
40.0f, -10.0f, 40.0f, 1.0f,
40.0f, -10.0f, 40.0f, 1.0f,
40.0f, -10.0f, -40.0f, 1.0f,
-40.0f, -10.0f, 40.0f, 1.0f };

float normalPlane[] = { 0.0f, 1.0f, 0.0f, 0.0f,
0.0f, -1.0f, 0.0f, 0.0f,
};

float colorsPlane[] = { 0.2f, 0.9f, 0.6f, 1.0f,
0.2f, 0.9f, 0.6f, 1.0f,
0.2f, 0.9f, 0.6f, 1.0f,
0.2f, 0.9f, 0.6f, 1.0f,
0.2f, 0.9f, 0.6f, 1.0f,
0.2f, 0.9f, 0.6f, 1.0f };

float texcoord_plane[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

/********************************************************************/

//Data for CUBE
float verticesDAKUWAQA[] = {
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f };

float normalDAKUWAQA[] = {
	-1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f };

float colorsDAKUWAQA[] = {
	0.583f, 0.771f, 0.014f, 1.0f,
	0.609f, 0.115f, 0.436f, 1.0f,
	0.327f, 0.483f, 0.844f, 1.0f,
	0.822f, 0.569f, 0.201f, 1.0f,
	0.435f, 0.602f, 0.223f, 1.0f,
	0.310f, 0.747f, 0.185f, 1.0f,
	0.597f, 0.770f, 0.761f, 1.0f,
	0.559f, 0.436f, 0.730f, 1.0f,
	0.359f, 0.583f, 0.152f, 1.0f,
	0.483f, 0.596f, 0.789f, 1.0f,
	0.559f, 0.861f, 0.639f, 1.0f,
	0.195f, 0.548f, 0.859f, 1.0f,
	0.014f, 0.184f, 0.576f, 1.0f,
	0.771f, 0.328f, 0.970f, 1.0f,
	0.406f, 0.615f, 0.116f, 1.0f,
	0.676f, 0.977f, 0.133f, 1.0f,
	0.971f, 0.572f, 0.833f, 1.0f,
	0.140f, 0.616f, 0.489f, 1.0f,
	0.997f, 0.513f, 0.064f, 1.0f,
	0.945f, 0.719f, 0.592f, 1.0f,
	0.543f, 0.021f, 0.978f, 1.0f,
	0.279f, 0.317f, 0.505f, 1.0f,
	0.167f, 0.620f, 0.077f, 1.0f,
	0.347f, 0.857f, 0.137f, 1.0f,
	0.055f, 0.953f, 0.042f, 1.0f,
	0.714f, 0.505f, 0.345f, 1.0f,
	0.783f, 0.290f, 0.734f, 1.0f,
	0.722f, 0.645f, 0.174f, 1.0f,
	0.302f, 0.455f, 0.848f, 1.0f,
	0.225f, 0.587f, 0.040f, 1.0f,
	0.517f, 0.713f, 0.338f, 1.0f,
	0.053f, 0.959f, 0.120f, 1.0f,
	0.393f, 0.621f, 0.362f, 1.0f,
	0.673f, 0.211f, 0.457f, 1.0f,
	0.820f, 0.883f, 0.371f, 1.0f,
	0.982f, 0.099f, 0.879f, 1.0f
};

/********************************************************************/

// Shader Names
char *vertexFileName = "particle.vert";
char *fragmentFileName = "particle.frag";
//char *geometryFileName = "particle.geo";
char *transformFileName = "particle.trans"; 
 
//for Particle VertexData
int num_particles = 100000;
float *particle_position_vbuffer;
float *particle_velocity_vbuffer;

// Program and Shader Identifiers
GLuint p,v,f;
 
// Vertex Attribute Locations
GLuint vertexLoc, colorLoc;
GLuint normalLoc;
GLuint texcoordLoc;
GLuint lightColorLoc;

 
// Uniform variable Locations
GLuint projMatrixLoc, viewMatrixLoc;
GLuint lightPositionLoc;
GLuint ambientLoc, diffuseLoc, specularLoc;
GLuint shininessLoc;
GLuint attenuationLoc;

//Uniform variable for Particles
GLuint particle_positionLoc;
GLuint particle_velocityLoc;

//data for texture
GLuint tex_name[2];

// Vertex Array Objects Identifiers
GLuint vao[1];

// storage for Matrices
float projMatrix[16];
float viewMatrix[16];
GLfloat lightPosition[4];

//storage for Vectors
float Red[] = {1.0f, 0.0f, 0.0f, 0.0f};
float Green[] = {0.0f, 1.0f, 0.0f, 0.0f};
float Blue[] = {0.0f, 0.0f, 1.0f, 0.0f};
float White[] = {1.0f, 1.0f, 1.0f, 0.0f};

//attenuations
float attenuations[] = { 0.5f, 0.5f, 0.5f, 1.0f };

/*******************************************************

			dakuwaqa: Vars & Functions

*******************************************************/
//camera control
int cameraX, cameraY, cameraZ;

void Cam_Poisition_Init(int camx, int camy, int camz)
{
	cameraX = camx;
	cameraY = camy;
	cameraZ = camz;
}

//  A pointer to a font style..
//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
//GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
/*
void printw(float x, float y, float z, char* format, ...)
{
	va_list args;   //  Variable argument list
	int len;        // String length
	int i;          //  Iterator
	char * text;    // Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1;

	//  Allocate memory for a string of the specified size
	text = (char*)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f(x, y, z);

	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}
*/

// ----------------------------------------------------
// VECTOR STUFF
//
 
// res = a cross b;
void crossProduct( float *a, float *b, float *res) {
 
    res[0] = a[1] * b[2]  -  b[1] * a[2];
    res[1] = a[2] * b[0]  -  b[2] * a[0];
    res[2] = a[0] * b[1]  -  b[0] * a[1];
}
 
// Normalize a vec3
void normalize(float *a) {
 
    float mag = sqrt(a[0] * a[0]  +  a[1] * a[1]  +  a[2] * a[2]);
 
    a[0] /= mag;
    a[1] /= mag;
    a[2] /= mag;
}
 
// ----------------------------------------------------
// MATRIX STUFF
//
 
// sets the square matrix mat to the identity matrix,
// size refers to the number of rows (or columns)
void setIdentityMatrix( float *mat, int size) {
 
    // fill matrix with 0s
    for (int i = 0; i < size * size; ++i)
            mat[i] = 0.0f;
 
    // fill diagonal with 1s
    for (int i = 0; i < size; ++i)
        mat[i + i * size] = 1.0f;
}
 
//
// a = a * b;
//
void multMatrix(float *a, float *b) {
 
    float res[16];
 
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            res[j*4 + i] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                res[j*4 + i] += a[k*4 + i] * b[j*4 + k];
            }
        }
    }
    memcpy(a, res, 16 * sizeof(float));
 
}
 
// Defines a transformation matrix mat with a translation
void setTranslationMatrix(float *mat, float x, float y, float z) {
 
    setIdentityMatrix(mat,4);
    mat[12] = x;
    mat[13] = y;
    mat[14] = z;
}

// ----------------------------------------------------
// Projection Matrix
//
 
void buildProjectionMatrix(float fov, float ratio, float nearP, float farP) {
 
    float f = 1.0f / tan (fov * (M_PI / 360.0)); //fovy
 
    setIdentityMatrix(projMatrix,4);
 
    projMatrix[0] = f / ratio;
    projMatrix[1 * 4 + 1] = f;
    projMatrix[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    projMatrix[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    projMatrix[2 * 4 + 3] = -1.0f;
    projMatrix[3 * 4 + 3] = 0.0f;
}

// ----------------------------------------------------
// (LIGHT)View Matrix for LIGHT
//
// note: it assumes the camera is not tilted,
// i.e. a vertical up vector (remmeber gluLookAt?)
//

// ----------------------------------------------------
// (CAMERA)View Matrix for CAMERA
//
// note: it assumes the camera is not tilted,
// i.e. a vertical up vector (remmeber gluLookAt?)
//
 
void setCamera(float posX, float posY, float posZ,
               float lookAtX, float lookAtY, float lookAtZ) {
 
    float dir[3], right[3], up[3];
 
    up[0] = 0.0f;   up[1] = 1.0f;   up[2] = 0.0f;
 
    dir[0] =  (lookAtX - posX);
    dir[1] =  (lookAtY - posY);
    dir[2] =  (lookAtZ - posZ);
    normalize(dir);
 
    crossProduct(dir,up,right);
    normalize(right);
 
    crossProduct(right,dir,up);
    normalize(up);
 
    float aux[16];
 
    viewMatrix[0]  = right[0];
    viewMatrix[4]  = right[1];
    viewMatrix[8]  = right[2];
    viewMatrix[12] = 0.0f;
 
    viewMatrix[1]  = up[0];
    viewMatrix[5]  = up[1];
    viewMatrix[9]  = up[2];
    viewMatrix[13] = 0.0f;
 
    viewMatrix[2]  = -dir[0];
    viewMatrix[6]  = -dir[1];
    viewMatrix[10] = -dir[2];
    viewMatrix[14] =  0.0f;
 
    viewMatrix[3]  = 0.0f;
    viewMatrix[7]  = 0.0f;
    viewMatrix[11] = 0.0f;
    viewMatrix[15] = 1.0f;
 
    setTranslationMatrix(aux, -posX, -posY, -posZ);
 
    multMatrix(viewMatrix, aux);
}
 
void setLightPosition()
{
	lightPosition[0] = 0.0f;
	lightPosition[1] = 1.0f;
	lightPosition[2] = 0.0f;
	lightPosition[3] = 1.0f;
}
// ----------------------------------------------------
 
void reshapeFunc(int w, int h) {
 
    float ratio;
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;
 
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
 
    ratio = (1.0f * w) / h;
    buildProjectionMatrix(53.13f, ratio, 1.0f, 30.0f);
}
/**************************************************************

		GLuint loadCubemap(vector<const GLchar*> faces) 

**************************************************************/
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void setupBuffers() {
 
    GLuint vbo[4];

    glGenVertexArrays(3, vao);
    //
    // VAO for first triangle
    //

	/*
    glBindVertexArray(vao[0]);
	//glEnable(GL_VERTEX_ARRAY);
	//glEnable(GL_COLOR_ARRAY);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
	*/

	glBindVertexArray(vao[0]);
	
	glGenBuffers(3, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorsCube), colorsCube, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalsCube), normalsCube, GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);
	
	//
	// VAO for PLANE
	//
	glBindVertexArray(vao[1]);
	// Generate two slots for the vertex and color buffers
	glGenBuffers(3, vbo);

	// bind buffer for vertices and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlane), verticesPlane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

	// bind buffer for colors and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorsPlane), colorsPlane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

	// bind buffer for normal and copy data into buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normalPlane), normalPlane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(normalLoc);
	glVertexAttribPointer(normalLoc, 4, GL_FLOAT, 0, 0, 0);

	/*
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcoord_plane), texcoord_plane, GL_STATIC_DRAW);
	glEnableVertexAttribArray(texcoordLoc);
	glVertexAttribPointer(texcoordLoc, 2, GL_FLOAT, 0, 0, 0);
	*/

	glBindVertexArray(vao[2]);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAxis), verticesAxis, GL_STATIC_DRAW);
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorAxis), colorAxis, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colorLoc);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);


	// Cubemap (Skybox)
	vector<const GLchar*> faces;
	faces.push_back("skybox/right.jpg");
	faces.push_back("skybox/left.jpg");
	faces.push_back("skybox/top.jpg");
	faces.push_back("skybox/bottom.jpg");
	faces.push_back("skybox/back.jpg");
	faces.push_back("skybox/front.jpg");
	GLuint cubemapTexture = loadCubemap(faces);

}
 
void setUniforms() {
 
    // must be called after glUseProgram
    glUniformMatrix4fv(projMatrixLoc,  1, false, projMatrix);
    glUniformMatrix4fv(viewMatrixLoc,  1, false, viewMatrix);
	glUniform4f(lightPositionLoc, 0.0f, 1.0f, 0.0f, 1.0f);

	//Colors
	glUniform4fv(ambientLoc, 1, White);
	glUniform4fv(diffuseLoc, 1, Blue);
	glUniform4fv(specularLoc, 1, Green);

	glUniform4fv(attenuationLoc, 1, attenuations);
	glUniform1f(shininessLoc, 1);
}
 
void renderFunc(void) {
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    setCamera(cameraX,cameraY,cameraZ,0,0,0);
	//setCamera(0, 0, 3, 0, 0, 0);

    glUseProgram(p);
    setUniforms();
 
	//drawing (TRIANGLE1)
	//glEnable(GL_POINT_SPRITE);
	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
 //   glBindVertexArray(vao[0]);
 //   glDrawArrays(GL_POINTS, 0, 4);
	//glDisable(GL_POINT_SPRITE);
	//glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
 
	/********************************************
	
				dakuwaqa : draw cube

	********************************************/
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	/********************************************

				dakuwaqa : draw plane

	********************************************/
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	/********************************************

				dakuwaqa : draw axis

	********************************************/
	glBindVertexArray(vao[2]);
	glDrawArrays(GL_LINES, 0, 6);

	//drawing (TRIANGLE2)
    //glBindVertexArray(vao[1]);
    //glDrawArrays(GL_LINES, 0, 6);
 
    glutSwapBuffers();
}
 

void processNormalKeys(unsigned char key, int x, int y) {
 
	switch (key)
	{
	case '27':
		glDeleteVertexArrays(5, vao);
		glDeleteProgram(p);
		glDeleteShader(v);
		glDeleteShader(f);
		exit(0);
	case 's':
	case 'S':
		cameraZ++;
		break;
	case 'w':
	case 'W':
		cameraZ--;
		break;
	case 'd':
	case 'D':
		cameraX++;
		break;
	case 'a':
	case 'A':
		cameraX--;
		break;
	case 'r':
	case 'R':
		cameraY++;
		break;
	case 'f':
	case 'F':
		cameraY--;
		break;
	}
}
 
#define printOpenGLError() printOglError(__FILE__, __LINE__)
 
int printOglError(char *file, int line)
{
    //
    // Returns 1 if an OpenGL error occurred, 0 otherwise.
    //
    GLenum glErr;
    int    retCode = 0;
 
    glErr = glGetError();
    while (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}
 
void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 
void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
 
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);
 
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}
 /*
GLuint setupTransformShader()
{
	char *ts = NULL;
	
	//malloc
	particle_position_vbuffer = (float*)malloc(sizeof(float) * 3 * num_particles);
	particle_velocity_vbuffer = (float*)malloc(sizeof(float) * 3 * num_particles);

	//program and shader handles
	GLuint tp;
	GLuint t;

	//create and compile vertex shader
	t = glCreateShader(GL_VERTEX_SHADER);
	ts = textFileRead(transformFileName);
	const char * tt = ts;
	glShaderSource(t, 1, &tt, NULL);
	free(ts);
	glCompileShader(t);
	printShaderInfoLog(t);

	//create program
	tp = glCreateProgram();

	//attach shaders
	glAttachShader(tp, t);

	//specify transform feedback output
	const char *varyings[] = {"v_position", "v_velocity"};
	glTransformFeedbackVaryings(tp, 2, varyings, GL_INTERLEAVED_ATTRIBS);

	//link the program and check for errors
	glLinkProgram(tp);

	GLint center_location = glGetUniformLocation(tp, "center");
	GLint radius_location = glGetUniformLocation(tp, "radius");
	GLint g_location = glGetUniformLocation(tp, "g");
	GLint dt_location = glGetUniformLocation(tp, "dt");
	GLint bounce_location = glGetUniformLocation(tp, "bounce");
	GLint seed_location = glGetUniformLocation(tp, "seed");
	
	setupParticleVertexData(particle_position_vbuffer, particle_velocity_vbuffer, num_particles);

	transform_setupBuffers();

	return(tp);

}
*/
void transform_setupBuffers()
{
	int buffercount = 2;
	//generate vbos and vaos
	GLuint vao[2], vbo[2];
	glGenVertexArrays(buffercount, vao);
	glGenBuffers(buffercount, vbo);

	for(int i=0; i<buffercount; i++)
	{
		glBindVertexArray(vao[i]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

		//fill with initial data
		glBufferData(GL_ARRAY_BUFFER, sizeof(particle_position_vbuffer), particle_position_vbuffer, GL_STATIC_DRAW);

		//setup generic attrib pointers
		glEnableVertexAttribArray(particle_positionLoc);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

		glEnableVertexAttribArray(particle_velocityLoc);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	}
	
	//"unbind" vao
	glBindVertexArray(0);

	//we ar blending so no depth testing
	glDisable(GL_DEPTH_TEST);

	//enable blending
	glEnable(GL_BLEND);
	//and set the blend function to result = 1*source + 1*destination
	glBlendFunc(GL_ONE, GL_ONE);


}
void setupParticleVertexData(float* p_position, float* p_velocity, int num_particles)
{
	//generate random 
	for(int i=0; i<num_particles; i++)
	{
		p_position[3*i]   = 0.5f - 5.0f * ((float)rand()/RAND_MAX);
		p_position[3*i+1] = 20.0f + 5.0f * (0.5f-(float)rand()/RAND_MAX);
		p_position[3*i+2] = 0.5f - 5.0f * ((float)rand()/RAND_MAX);
		
	}

	//set initial particle velocity
	for(int i=0; i<num_particles; i++)
	{
		p_velocity[3*i]   = 0.0f;
		p_velocity[3*i+1] = 0.0f;
		p_velocity[3*i+2] = 0.0f;
	}
}
GLuint setupShaders() {
 
    char *vs = NULL;
	char *fs = NULL;
	char *fs2 = NULL;
	
	/*************************  geometry shader  *******************************/
	char *gs = NULL;
 
    GLuint p,v,f;
	/*************************  geometry shader  *******************************/
	//GLuint g;

    v = glCreateShader(GL_VERTEX_SHADER);
	/*************************  geometry shader  *******************************/
	//g = glCreateShader(GL_GEOMETRY_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
 
    vs = textFileRead(vertexFileName);
	/*************************  geometry shader  *******************************/
	//gs = textFileRead(geometryFileName);
    fs = textFileRead(fragmentFileName);

    const char * vv = vs;
	//const char * gg = gs;
    const char * ff = fs;
 
    glShaderSource(v, 1, &vv,NULL);
	/*************************  geometry shader  *******************************/
	/************************* 2015-01-19(ERROR) *******************************/
	//glShaderSource(g, 1, &gg, NULL);
    glShaderSource(f, 1, &ff,NULL);
	/*
	The length​ can be either NULL or an array of count​ integers. 
	These are the lengths of the corresponding strings in the string​ array. 
	This allows you to use non-NULL-terminated strings. 
	If you pass NULL,
		then OpenGL will assume all of the strings are NULL-terminated and will therefore compute the length in the usual way.
	*/

    free(vs);
	//free(gs);
	free(fs);
 
    glCompileShader(v);
	//glCompileShader(g);
    glCompileShader(f);
 
    printShaderInfoLog(v);
	//printShaderInfoLog(g);
    printShaderInfoLog(f);
	
 
    p = glCreateProgram();
    glAttachShader(p,v);
	//glAttachShader(p,g);
    glAttachShader(p,f);
 
    glBindFragDataLocation(p, 0, "outputF");
    glLinkProgram(p);
    printProgramInfoLog(p);
 
    vertexLoc = glGetAttribLocation(p,"a_position");
    colorLoc = glGetAttribLocation(p, "a_color"); 
	normalLoc = glGetAttribLocation(p, "a_normal");
	texcoordLoc = glGetAttribLocation(p, "a_texCoord");

    projMatrixLoc = glGetUniformLocation(p, "u_projMatrix");
    viewMatrixLoc = glGetUniformLocation(p, "u_viewMatrix");
	lightPositionLoc = glGetUniformLocation(p, "u_lightPosition");

	ambientLoc = glGetUniformLocation(p, "u_ambient");
	diffuseLoc = glGetUniformLocation(p, "u_diffuse");
	specularLoc = glGetUniformLocation(p, "u_specular");
	shininessLoc = glGetUniformLocation(p, "u_shininess");
	
    return(p);
}
 
int main(int argc, char **argv) {

	Cam_Poisition_Init(0, 5, 5);
	//printw(0, 0, 5, "cameraX : %d, cameraY : %d, cameraZ : %d", cameraX, cameraY, cameraZ);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
	glutInitWindowSize(512, 512);
    glutCreateWindow("SHADERMASTER_SUNGJOO");

	glutDisplayFunc(renderFunc);
    glutIdleFunc(renderFunc);
    glutReshapeFunc(reshapeFunc);
    glutKeyboardFunc(processNormalKeys);

    glewInit();
    if (glewIsSupported("GL_VERSION_3_3"))
        printf("Ready for OpenGL 3.3\n");
    else {
        printf("OpenGL 3.3 not supported\n");
        exit(1);
    }

	//glDisable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING)
	//glEnable(GL_LIGHT0)

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0,0.0,0.0,1.0);
 
	//setupTextures();

    p = setupShaders(); 
    setupBuffers(); 

    glutMainLoop();
 
    return(0); 
}
