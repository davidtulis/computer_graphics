#include <stdlib.h>             // to define exit(0)

#ifdef __APPLE__
#  include <GL/glew.h>

#include <GLUT/glut.h>
#  include <GLUT/glut.h>

#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "getbmp.h"

static float angle=0;
static float radius=5;
static int sideNum=0;

//TEXTURES
static unsigned int externalTextures[2];
static unsigned int internalTextures[6];
static unsigned char sides[6][8][8][4];

void loadExternalTextures()
{
	// Local storage for bmp image data.
	BitMapFile *image[2];
   
	image[0] = getbmp("space.bmp");
	image[1] = getbmp("cat.bmp");
	
	// Bind cat image to texture object internalTextures[0]. 
   glBindTexture(GL_TEXTURE_2D, externalTextures[0]); 
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

   // Bind space image to texture object internalTextures[1]
   glBindTexture(GL_TEXTURE_2D, externalTextures[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0, 
	            GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);		
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);		
}

void loadInternalTextures(){
   for (int i=0;i<6; i++)
   {
		// Create texture object internalTextures[i]. 
		glBindTexture(GL_TEXTURE_2D, internalTextures[i]); 
		// Specify image data for currently active texture object.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, sides[i]);
	      
		// Set texture parameters for wrapping.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set texture parameters for filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   }
}

void drawDot(int side, int i, int j)
{
	sides[side][i][j][0]=0x00;
	sides[side][i][j][1]=0x00;
	sides[side][i][j][2]=0x00;
	sides[side][i][j][3]=0xFF;
}

void createTextures() 
{
	//set color of the cube
	for (int k=0; k<6; k++) 
	{
		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			{
				sides[k][i][j][0] = 0xFF;
				sides[k][i][j][1] = 0xFF;
				sides[k][i][j][2] = 0xFF;
				sides[k][i][j][3] = 0xFF; 
			}
		}
	}
	
	//one
	drawDot(0, 4, 4);

	//two
	drawDot(1, 2, 2);
	drawDot(1, 6, 6);
		
	//three
	drawDot(2, 2, 2);
	drawDot(2, 4, 4);
	drawDot(2, 6, 6);
	
	//four
	drawDot(3, 2, 2);
	drawDot(3, 6, 2);
	drawDot(3, 6, 6);
	drawDot(3, 2, 6);
	
	//five
	drawDot(4, 2, 2);
	drawDot(4, 6, 2);
	drawDot(4, 6, 6);
	drawDot(4, 2, 6);
	drawDot(4, 4, 4);
	
	//six
	drawDot(5, 2, 2);
	drawDot(5, 4, 2);
	drawDot(5, 6, 2);
	drawDot(5, 2, 6);
	drawDot(5, 4, 6);
	drawDot(5, 6, 6);
}

// Initialization routine.
void setup(void) 
{	
	//LIGHTING 
	//The lighting seems to pulse because the rotation
	//causes the spotlight to change intensity, based off 
	//of intensity
	// Turn on OpenGL lighting.
	glColor3f(1,1,1);
	glEnable(GL_LIGHTING);
	
	glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 }; // ambient light
	float lightDiffusion[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
   
	
	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffusion);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
    glEnable(GL_LIGHT0); // Enable particular light source.
    
	// Material property vectors.
	float matSpec[] = {1.0, 1.0, 1.0, 1.0};
	float matShine[] = {50.0};
	float matAmb[] = {1.0, 1.0, 1.0, 1.0};
	float matDiff[] = {1.0, 1.0, 1.0, 1.0};

	// Material properties.
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    
	//TEXTURES
	glEnable(GL_DEPTH_TEST);

	// Create texture ids.
	glGenTextures(6, internalTextures); 
	glGenTextures(2, externalTextures);

	// Generate procedural texture.
	createTextures();

	// Load procedural texture.
	loadInternalTextures();
   
	loadExternalTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glLoadIdentity();
	gluLookAt(0.0, 5.0, 90.0, 0.0, 25.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();

	// Activate texture object.
	glTranslatef(0.0, 20.0, -65);

	glRotatef(angle, 1.0, 1.0, 0.0); 

	//front
	glBindTexture(GL_TEXTURE_2D, internalTextures[0]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
		glTexCoord2f(1, 0.0); glVertex3f(10.0, -10.0, 10.0);
		glTexCoord2f(1, 1); glVertex3f(10.0, 10.0, 10.0);
		glTexCoord2f(0.0, 1); glVertex3f(-10.0, 10.0, 10.0);
	glEnd();
   
	//bottom
	glBindTexture(GL_TEXTURE_2D, internalTextures[1]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
		glTexCoord2f(1, 0.0); glVertex3f(10.0, -10.0, 10.0);
		glTexCoord2f(1, 1); glVertex3f(10.0, -10.0, -10.0);
		glTexCoord2f(0.0, 1); glVertex3f(-10.0, -10.0, -10.0);
	glEnd();
   
	//top
	glBindTexture(GL_TEXTURE_2D, internalTextures[2]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, 10.0, 10.0);
		glTexCoord2f(1, 0.0); glVertex3f(10.0, 10.0, 10.0);
		glTexCoord2f(1, 1); glVertex3f(10.0, 10.0, -10.0);
		glTexCoord2f(0.0, 1); glVertex3f(-10.0, 10.0, -10.0);
	glEnd();
   
	//left
	glBindTexture(GL_TEXTURE_2D, internalTextures[3]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 10.0);
		glTexCoord2f(1, 0.0); glVertex3f(-10.0, 10.0, 10.0);
		glTexCoord2f(1, 1); glVertex3f(-10.0, 10.0, -10.0);;
		glTexCoord2f(0.0, 1); glVertex3f(-10.0, -10.0, -10.0);
	glEnd();
   
	//right
	glBindTexture(GL_TEXTURE_2D, internalTextures[4]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(10.0, 10.0, 10.0);
		glTexCoord2f(1, 0.0); glVertex3f(10.0, -10.0, 10.0);
		glTexCoord2f(1, 1); glVertex3f(10.0, -10.0, -10.0);;
		glTexCoord2f(0.0, 1); glVertex3f(10.0, 10.0, -10.0);
	glEnd();
   
	//back
	glBindTexture(GL_TEXTURE_2D, internalTextures[5]); 
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, -10.0);
		glTexCoord2f(1, 0.0); glVertex3f(10.0, -10.0, -10.0);
		glTexCoord2f(1, 1); glVertex3f(10.0, 10.0, -10.0);
		glTexCoord2f(0.0, 1); glVertex3f(-10.0, 10.0, -10.0);
	glEnd();
   
	glPopMatrix();

	//for the ground and sky
	glBindTexture(GL_TEXTURE_2D, externalTextures[0]);        
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, 0.0, 100.0);
		glTexCoord2f(8.0, 0.0); glVertex3f(100.0, 0.0, 100.0);
		glTexCoord2f(8.0, 8.0); glVertex3f(100.0, 0.0, -100.0);
		glTexCoord2f(0.0, 8.0); glVertex3f(-100.0, 0.0, -100.0);
	glEnd();

	// Map the sky texture onto a rectangle parallel to the xy-plane.
	glBindTexture(GL_TEXTURE_2D, externalTextures[1]);        
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3f(-100.0, 0.0, -70.0);
		glTexCoord2f(1.0, 0.0); glVertex3f(100.0, 0.0, -70.0);
		glTexCoord2f(1.0, 1.0); glVertex3f(100.0, 120.0, -70.0);
		glTexCoord2f(0.0, 1.0); glVertex3f(-100.0, 120.0, -70.0);
	glEnd();
   
	glutSwapBuffers();	
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    float aspect = w*1.0/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, aspect, 0.1, 250);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:                  // escape
         exit(0);
         break;
      default:
         break;
   }
}

void cameraMotion(void) 
{
	angle+= 3;
	if (angle > 360.0) 
		angle -= 360.0;
	glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("HW5");
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
	glutKeyboardFunc(keyInput);
    glutIdleFunc(cameraMotion);

	glewExperimental = GL_TRUE;
	glewInit();

	setup(); 
   
	glutMainLoop(); 
}
