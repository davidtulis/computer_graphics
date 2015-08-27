///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
// 
// Sumanta Guha.
///////////////////////////////////

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

// Drawing routine.
void drawScene(void)
{
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   //T
	glBegin(GL_POLYGON);
		glVertex3f(10.0, 30.0, 0.0);
		glVertex3f(10.0, 29.0, 0.0);
		glVertex3f(25.0, 29.0, 0.0);
		glVertex3f(25.0, 30.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(17.0, 29.0, 0.0);
		glVertex3f(19.0, 29.0, 0.0);
		glVertex3f(19.0, 15.0, 0.0);
		glVertex3f(17.0, 15.0, 0.0);
	glEnd();

	//O
	glBegin(GL_POLYGON);
		glVertex3f(30.0, 30.0, 0.0);
		glVertex3f(40.0, 30.0, 0.0);
		glVertex3f(40.0, 15.0, 0.0);
		glVertex3f(30.0, 15.0, 0.0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(34.0, 28.0, 0.0);
		glVertex3f(36.0, 28.0, 0.0);
		glVertex3f(36.0, 17.0, 0.0);
		glVertex3f(34.0, 17.0, 0.0);
	glEnd();

	//P
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(43.0, 30.0, 0.0);
		glVertex3f(45.0, 30.0, 0.0);
		glVertex3f(45.0, 15.0, 0.0);
		glVertex3f(43.0, 15.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(43.0, 30.0, 0.0);
		glVertex3f(50.0, 30.0, 0.0);
		glVertex3f(50.0, 25.0, 0.0);
		glVertex3f(43.0, 25.0, 0.0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(45.0, 28.0, 0.0);
		glVertex3f(49.0, 28.0, 0.0);
		glVertex3f(49.0, 26.0, 0.0);
		glVertex3f(45.0, 26.0, 0.0);
	glEnd();

	//K
	glColor3f(0.5, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(51.0, 30.0, 0.0);
		glVertex3f(53.0, 30.0, 0.0);
		glVertex3f(53.0, 15.0, 0.0);
		glVertex3f(51.0, 15.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(53.0, 25.0, 0.0);
		glVertex3f(58.0, 30.0, 0.0);
		glVertex3f(60.0, 30.0, 0.0);
		glVertex3f(53.0, 23.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(53.0, 25.0, 0.0);
		glVertex3f(58.0, 15.0, 0.0);
		glVertex3f(60.0, 15.0, 0.0);
		glVertex3f(53.0, 23.0, 0.0);
	glEnd();

	//E
	glColor3f(0.0, 0.5, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(61.0, 30.0, 0.0);
		glVertex3f(71.0, 30.0, 0.0);
		glVertex3f(71.0, 15.0, 0.0);
		glVertex3f(61.0, 15.0, 0.0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(63.0, 28.0, 0.0);
		glVertex3f(71.0, 28.0, 0.0);
		glVertex3f(71.0, 24.0, 0.0);
		glVertex3f(63.0, 24.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(63.0, 22.0, 0.0);
		glVertex3f(71.0, 22.0, 0.0);
		glVertex3f(71.0, 17.0, 0.0);
		glVertex3f(63.0, 17.0, 0.0);
	glEnd();
	
	//K
	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
		glVertex3f(74.0, 30.0, 0.0);
		glVertex3f(76.0, 30.0, 0.0);
		glVertex3f(76.0, 15.0, 0.0);
		glVertex3f(74.0, 15.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(76.0, 25.0, 0.0);
		glVertex3f(81.0, 30.0, 0.0);
		glVertex3f(83.0, 30.0, 0.0);
		glVertex3f(76.0, 23.0, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(76.0, 25.0, 0.0);
		glVertex3f(81.0, 15.0, 0.0);
		glVertex3f(83.0, 15.0, 0.0);
		glVertex3f(76.0, 23.0, 0.0);
	glEnd();
   glFlush(); 
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
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
   glutCreateWindow("square.cpp");
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 
   
   glutMainLoop(); 
}
