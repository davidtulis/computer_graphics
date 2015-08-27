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
const float radius = 10.0;
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


void drawCube() {
	glColor3f((double) rand()/RAND_MAX, (double) rand()/RAND_MAX, (double) rand()/RAND_MAX);
	glScalef(0.3, 0.3, 1);

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);

}

// Drawing routine.
void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float angle;
	float x;
	float y;
	
	//make sure we aren't outside of the clipping plane
	glTranslatef(0, 0, -20);
	    glLineWidth(2);

	for (int i=0; i<12; i++)
	{
		glPushMatrix();
		float angle = (PI/6)*i;	//radians
		x = xOrigin+(radius)*cos (angle); //250+
		y = yOrigin+(radius)*sin (angle);
		glColor3f((double) rand()/RAND_MAX, (double) rand()/RAND_MAX, (double) rand()/RAND_MAX);
		
		glTranslatef(x, y, 0);
		glRotatef((180/PI)*angle+90, 0, 0, 1);
		glScalef(0.8, 6, 1);

		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);		glPopMatrix();
	}
	
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
   glutCreateWindow("hw3pt2.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
