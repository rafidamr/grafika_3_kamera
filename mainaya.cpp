#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.hpp>
#include <controls.hpp>

using namespace glm;

GLFWwindow* window;

void initGLFW();
GLfloat* drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, int side );
GLfloat* drawCylinder( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLint numberOfSides );
void appendArray(GLfloat* array1, int sizeArray1, GLfloat* array2, int sizeArray2, GLfloat* arrayResult);


int main(void)
{
	// Initialise GLFW
	initGLFW();

	// White background
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("VertexShader.vertexshader", "FragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	
	// for (int i = 0; i < 360; i++) {
	// 	printf("%f \n", vertex[i]);
	// }
	GLfloat _vertex[]={
		//front bottom
		-1.0f,-0.8, 1.0f,
		-1.0f,-0.8, 2.0f,
		-1.0f, -0.25f, 2.0f,
		1.0f, -0.25f, 1.0f,
		-1.0f,-0.8, 1.0f,
		-1.0f, -0.25f, 1.0f,

		// 1.0f,-0.8, 2.0f,
		// -1.0f,-0.8, 1.0f,
		// 1.0f,-0.8, 1.0f,
		// 1.0f, -0.25f, 1.0f,
		// 1.0f,-0.8, 1.0f,
		// -1.0f,-0.8, 1.0f,

		// -1.0f,-0.8, 1.0f,
		// -1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 1.0f,
		// 1.0f,-0.8, 2.0f,
		// -1.0f,-0.8, 2.0f,
		// -1.0f,-0.8, 1.0f,

		// -1.0f,-0.25f, 2.0f,
		// -1.0f,-0.8, 2.0f,
		// 1.0f,-0.8, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f,-0.8, 1.0f,
		// 1.0f, -0.25f, 1.0f,

		// 1.0f,-0.8, 1.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f,-0.8, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 1.0f,
		// -1.0f, -0.25f, 1.0f,

		// 1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 1.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f,-0.8, 2.0f,

		// //front upper 1
		// -1.0f, -0.25f, 1.0f,
		// -1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f, 0, 1.0f,
		// -1.0f, -0.25f, 1.0f,
		// -1.0f, 0, 1.0f,

		// 1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 1.0f,
		// 1.0f, -0.25f, 1.0f,
		// 1.0f, 0, 1.0f,
		// 1.0f, -0.25f, 1.0f,
		// -1.0f, -0.25f, 1.0f,

		// -1.0f, -0.25f, 1.0f,
		// -1.0f, -0.25f, 2.0f,
		// -1.0f, 0, 1.0f,
		// 1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 1.0f,

		// -1.0f,-0.25f, 2.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 1.0f,
		// 1.0f, 0, 1.0f,

		// 1.0f, -0.25f, 1.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// 1.0f, 0, 1.0f,
		// -1.0f, 0, 1.0f,

		// 1.0f, -0.25f, 2.0f,
		// -1.0f, 0, 1.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,
		// -1.0f, -0.25f, 2.0f,
		// 1.0f, -0.25f, 2.0f,

		// //front bottom 2
		// -1.0f,-0.8, 0.6f,
		// -1.0f,-0.8, 1.0f,
		// -1.0f, 0, 1.0f,
		// 1.0f, 0, 0.6f,
		// -1.0f,-0.8, 0.6f,
		// -1.0f, 0, 0.6f,

		// 1.0f,-0.8, 1.0f,
		// -1.0f,-0.8, 0.6f,
		// 1.0f,-0.8, 0.6f,
		// 1.0f, 0, 0.6f,
		// 1.0f,-0.8, 0.6f,
		// -1.0f,-0.8, 0.6f,

		// -1.0f,-0.8, 0.6f,
		// -1.0f, 0, 1.0f,
		// -1.0f, 0, 0.6f,
		// 1.0f,-0.8, 1.0f,
		// -1.0f,-0.8, 1.0f,
		// -1.0f,-0.8, 0.6f,

		// -1.0f,0, 1.0f,
		// -1.0f,-0.8, 1.0f,
		// 1.0f,-0.8, 1.0f,
		// 1.0f, 0, 1.0f,
		// 1.0f,-0.8, 0.6f,
		// 1.0f, 0, 0.6f,

		// 1.0f,-0.8, 0.6f,
		// 1.0f, 0, 1.0f,
		// 1.0f,-0.8, 1.0f,
		// 1.0f, 0, 1.0f,
		// 1.0f, 0, 0.6f,
		// -1.0f, 0, 0.6f,

		// 1.0f, 0, 1.0f,
		// -1.0f, 0, 0.6f,
		// -1.0f, 0, 1.0f,
		// 1.0f, 0, 1.0f,
		// -1.0f, 0, 1.0f,
		// 1.0f,-0.8, 1.0f,

		// //front upper
		// -1.0f, 0, 0.6f,
		// -1.0f, 0, 1.0f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0, 0.6f,
		// -1.0f, 0.7f, 0.6f,

		// 1.0f, 0, 1.0f,
		// -1.0f, 0, 0.6f,
		// 1.0f, 0, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f, 0, 0.6f,
		// -1.0f, 0, 0.6f,

		// -1.0f, 0, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0, 1.0f,
		// -1.0f, 0, 1.0f,
		// -1.0f, 0, 0.6f,

		// -1.0f,0.7f, 0.6f,
		// -1.0f, 0, 1.0f,
		// 1.0f, 0, 1.0f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f, 0, 0.6f,
		// 1.0f, 0.7f, 0.6f,

		// 1.0f, 0, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f, 0, 1.0f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,

		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0, 1.0f,

		// //mid
		// -1.0f,-1.0f,-1.5f,
		// -1.0f,-1.0f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f,-1.5f,
		// -1.0f,-1.0f,-1.5f,
		// -1.0f, 0.7f,-1.5f,

		// 1.0f,-1.0f, 0.6f,
		// -1.0f,-1.0f,-1.5f,
		// 1.0f,-1.0f,-1.5f,
		// 1.0f, 0.7f,-1.5f,
		// 1.0f,-1.0f,-1.5f,
		// -1.0f,-1.0f,-1.5f,

		// -1.0f,-1.0f,-1.5f,
		// -1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f,-1.5f,
		// 1.0f,-1.0f, 0.6f,
		// -1.0f,-1.0f, 0.6f,
		// -1.0f,-1.0f,-1.5f,

		// -1.0f, 0.7f, 0.6f,
		// -1.0f,-1.0f, 0.6f,
		// 1.0f,-1.0f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f,-1.0f,-1.5f,
		// 1.0f, 0.7f,-1.5f,

		// 1.0f,-1.0f,-1.5f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f,-1.0f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f,-1.5f,
		// -1.0f, 0.7f,-1.5f,

		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f,-1.5f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f, 0.7f, 0.6f,
		// -1.0f, 0.7f, 0.6f,
		// 1.0f,-1.0f, 0.6f,

		// //back upper
		// -1.0f, 0,-2.0f,
		// -1.0f, 0, -1.5f,
		// -1.0f, 0.7f, -1.5f,
		// 1.0f, 0.7f, -1.5f,
		// -1.0f, 0,-2.0f,
		// -1.0f, 0.7f, -1.5f,

		// 1.0f, 0, -1.5f,
		// -1.0f, 0,-2.0f,
		// 1.0f, 0,-2.0f,
		// 1.0f, 0.7f, -1.5f,
		// 1.0f, 0,-2.0f,
		// -1.0f, 0,-2.0f,

		// -1.0f, 0,-2.0f,
		// -1.0f, 0.7f, -1.5f,
		// -1.0f, 0.7f, -1.5f,
		// 1.0f, 0, -1.5f,
		// -1.0f, 0, -1.5f,
		// -1.0f, 0,-2.0f,

		// -1.0f, 0.7f, -1.5f,
		// -1.0f, 0, -1.5f,
		// 1.0f, 0, -1.5f,
		// 1.0f, 0.7f, -1.5f,
		// 1.0f, 0,-2.0f,
		// 1.0f, 0.7f, -1.5f,

		// 1.0f, 0,-2.0f,
		// 1.0f, 0.7f, -1.5f,
		// 1.0f, 0, -1.5f,
		// 1.0f, 0.7f, -1.5f,
		// 1.0f, 0.7f, -1.5f,
		// -1.0f, 0.7f, -1.5f,

		// 1.0f, 0.7f, -1.5f,
		// -1.0f, 0.7f, -1.5f,
		// -1.0f, 0.7f, -1.5f,
		// 1.0f, 0.7f, -1.5f,
		// -1.0f, 0.7f, -1.5f,
		// 1.0f, 0, -1.5f,

		// //back bottom
		// -1.0f,-1.0f,-2.0f,
		// -1.0f,-1.0f, -1.5f,
		// -1.0f, 0, -1.5f,
		// 1.0f, 0,-2.0f,
		// -1.0f,-1.0f,-2.0f,
		// -1.0f, 0,-2.0f,

		// 1.0f,-1.0f, -1.5f,
		// -1.0f,-1.0f,-2.0f,
		// 1.0f,-1.0f,-2.0f,
		// 1.0f, 0,-2.0f,
		// 1.0f,-1.0f,-2.0f,
		// -1.0f,-1.0f,-2.0f,

		// -1.0f,-1.0f,-2.0f,
		// -1.0f, 0, -1.5f,
		// -1.0f, 0,-2.0f,
		// 1.0f,-1.0f, -1.5f,
		// -1.0f,-1.0f, -1.5f,
		// -1.0f,-1.0f,-2.0f,

		// -1.0f,0, -1.5f,
		// -1.0f,-1.0f, -1.5f,
		// 1.0f,-1.0f, -1.5f,
		// 1.0f, 0, -1.5f,
		// 1.0f,-1.0f,-2.0f,
		// 1.0f, 0,-2.0f,

		// 1.0f,-1.0f,-2.0f,
		// 1.0f, 0, -1.5f,
		// 1.0f,-1.0f, -1.5f,
		// 1.0f, 0, -1.5f,
		// 1.0f, 0,-2.0f,
		// -1.0f, 0,-2.0f,

		// 1.0f, 0, -1.5f,
		// -1.0f, 0,-2.0f,
		// -1.0f, 0, -1.5f,
		// 1.0f, 0, -1.5f,
		// -1.0f, 0, -1.5f,
		// 1.0f,-1.0f, -1.5f,

		// //tes
		// 2.0f,0.0f,1.0f,
		// 2.0f,0.0f,0.0f,
		// 2.0f,0.7f,1.0f,
		// 2.0f,0.7f,0.0f,
		// 2.0f,0.7f,1.0f,
		// 2.0f,0.0f,0.0f,
	};

	int sides = 8;
	GLfloat* vertex1 = drawCircle(0.0f, 0.0f, 0.0f, 1.0f, sides, -1);
	GLfloat* vertex = drawCircle(1.0f, -0.8f, 0.6f, 0.3f, sides, -1);

	// GLfloat* vertex = (GLfloat*) malloc (( sides + 2 ) * 9 * 2 * sizeof(GLfloat));
	// appendArray(vertex2, (sides + 2) * 9, vertex1, (sides + 2) * 9, vertex);

	// // // // GLfloat* trybro = drawCircle(2.0f, 0.0f, 0.0f, 2.0f, 360);
	for (int i = 0; i < (sides + 2) * 9 ; i++) {
		printf("[%d]. %f\n", i, vertex[i]);
	}

	GLfloat color[] = {
		// front
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,
		0.9, 0.11, 0.11,

		// mid
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,
		0.96, 0.26, 0.21,

		// back
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,

		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,

		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,

		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,

		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,

		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
		0.72, 0.11, 0.11,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (sides + 2) * 9, vertex, GL_STATIC_DRAW);

	GLuint vertexbuffercolor;
	glGenBuffers(1, &vertexbuffercolor);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffercolor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

	//glTranslatef(0,0,2);

	do {

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		// 2nd attribute buffer : color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffercolor);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, (sides + 2) * 9 * 4); // 6 faces, 2 trianges, 3 vertices, start from 0

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

void initGLFW() {
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Kijang", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(1);
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited movement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
}

GLfloat* drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, int side )
{
    int numberOfVertices = numberOfSides + 2;
    
    GLfloat twicePi = 2.0f * M_PI;
    
    GLfloat circleVerticesX[numberOfSides+1];
    GLfloat circleVerticesY[numberOfSides+1];
    GLfloat circleVerticesZ[numberOfSides+1];
    
    GLfloat tempX, tempY, tempZ;
    circleVerticesX[0] = x;
    circleVerticesY[0] = y;
    circleVerticesZ[0] = z;
    
    for (long int i = 1; i <= numberOfVertices; i++ )
    {
    	circleVerticesX[i] = x;

    	if (side == 1) {
    		circleVerticesY[i] = y + ( radius * cos( i * twicePi / numberOfSides ) );
       		circleVerticesZ[i] = z + ( radius * sin( i *  twicePi / numberOfSides ) );
    	} else {
    		circleVerticesY[i] = y + ( radius * sin( i * twicePi / numberOfSides ) );
        	circleVerticesZ[i] = z + ( radius * cos( i *  twicePi / numberOfSides ) );
    	}
        
        // printf("Circle Vertice %ld X: %f\n", i, circleVerticesX[i]);
        // printf("Circle Vertice %ld Y: %f\n", i, circleVerticesY[i]);
        // printf("Circle Vertice %ld Z: %f\n", i, circleVerticesZ[i]);
    }

    // printf("TESTES\n");
    // printf("[%d] X %f\n", 1,circleVerticesX[1]);
    // printf("[%d] Y %f\n", 1,circleVerticesY[1]);
    // printf("[%d] Z %f\n", 1,circleVerticesZ[1]);
    
    GLfloat* allCircleVertices = (GLfloat*) malloc (( numberOfVertices ) * 9 * sizeof(GLfloat));
    
    int j = 1;
    for (long int i = 0; i < numberOfVertices; i++ )
    {
    	allCircleVertices[(i*9)-9] = circleVerticesX[0];
    	allCircleVertices[(i*9)-8] = circleVerticesY[0];
    	allCircleVertices[(i*9)-7] = circleVerticesZ[0];

    	allCircleVertices[(i*9)-6] = circleVerticesX[i];
    	allCircleVertices[(i*9)-5] = circleVerticesY[i];
    	allCircleVertices[(i*9)-4] = circleVerticesZ[i];

    	allCircleVertices[(i*9)-3] = circleVerticesX[i+1];
    	allCircleVertices[(i*9)-2] = circleVerticesY[i+1];
    	allCircleVertices[(i*9)-1] = circleVerticesZ[i+1];
    }

    allCircleVertices[(numberOfSides*9)-9] = circleVerticesX[0];
	allCircleVertices[(numberOfSides*9)-8] = circleVerticesY[0];
	allCircleVertices[(numberOfSides*9)-7] = circleVerticesZ[0];

	allCircleVertices[(numberOfSides*9)-6] = circleVerticesX[numberOfSides];
	allCircleVertices[(numberOfSides*9)-5] = circleVerticesY[numberOfSides];
	allCircleVertices[(numberOfSides*9)-4] = circleVerticesZ[numberOfSides];

	allCircleVertices[(numberOfSides*9)-3] = circleVerticesX[1];
	allCircleVertices[(numberOfSides*9)-2] = circleVerticesY[1];
	allCircleVertices[(numberOfSides*9)-1] = circleVerticesZ[1];

    return allCircleVertices;
}

GLfloat* drawCylinder( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLint numberOfSides ) {
	return 0;
}

void appendArray(GLfloat* array1, int sizeArray1, GLfloat* array2, int sizeArray2, GLfloat* arrayResult) {

	for (int i = 0; i < sizeArray1; i++) {
		arrayResult[i] = array1[i];	
	}

	int j = 0;
	for (int i = sizeArray1; i < sizeArray1 + sizeArray2; i++) {
		arrayResult[i] = array2[j];
		j++;
	}
}