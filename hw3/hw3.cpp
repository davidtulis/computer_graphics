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



// Drawing routine.
void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glScalef(3, 1, 1);
	glTranslatef(0, -3, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glScalef(-3, 1, 1.5);
	glTranslatef(0, -2, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glScalef(-2.5, 1, 2);
	glTranslatef(0, -0.3, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glScalef(-1.5, 1, 2);
	glTranslatef(0, 1.75, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glScalef(-0.5, -1.5, 2);
	glTranslatef(0, -2.9, 0);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, ordered);
	glPopMatrix();
   
   
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
   	glFrustum(-4, 4, -4, 4, 0.4, 2);

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
   glutCreateWindow("hw3.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
