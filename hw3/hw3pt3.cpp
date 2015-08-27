#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif
#include <cmath>
#include <stdio.h>
#include <iostream>
#define PI 3.14159265359

static int hour=0;
static int minute=0;
static int second=0;
const int numberOfPetals=12;
const float radius = 15.0;
const float xOrigin = 0;
const float yOrigin = 0;


static float vertices[] = {
	-1, -1, -0.5, //0
	1, -1, -0.5, //1
	1, 1, -0.5, //2
	-1, 1, -0.5, //3
	-1, -1, -0.7, //4
	1, -1, -0.7, //5
	1, 1, -0.7, //6
	-1, 1, -0.7  //7
	};

static unsigned int ordered[] = {
	0, 1, 
	1, 2,
	2, 3,
	3, 0,
	
	//back
	4, 5, 
	5, 6, 
	6, 7, 
	7, 4, 
	
	//connecting lines
	0, 4, 
	1, 5, 
	2, 6,
	3, 7};

		float angle;
		float x,y;
		
		
void drawPattern(int depthParameter) {
	
	if (depthParameter<1) 
	{
		return;
	}
	else
	{
		for (int i=0; i<numberOfPetals; i++)
		{
			glPushMatrix();

			angle = (PI/6)*i;
			x = (radius)*cos (angle); 
			y = (radius)*sin (angle);
			
			glTranslatef(x, y, 0);
			
			drawPattern(depthParameter-1);
		
			glRotatef((180/PI)*angle+90, 0, 0, 1);
			glScalef(0.8, 6, 1);
			glColor3f((double) rand()/RAND_MAX, (double) rand()/RAND_MAX, (double) rand()/RAND_MAX);
			glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
			glPopMatrix();
		}
		return;
	}
	
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//make sure we aren't outside of the clipping plane
	glTranslatef(0, 0, -20);
	glLineWidth(2);
	
	drawPattern(2);
	
	glFlush(); 
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 

	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, vertices);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glFrustum(-4, 4, -4, 4, 0.4, 2);
	glFrustum(-2, 2, -2, 2, 1, 300);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv) 
{
   glutInit(&argc, argv);

   glutInitContextVersion(1, 4);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("hw3pt3cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}

