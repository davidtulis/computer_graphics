//This program displays an analog clock on the screen
//By David Tulis

#include <stdio.h>
#include <time.h>
#include <cmath>
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
#define PI 3.14159265359
using namespace std;

static int hour=0;
static int minute=0;
static int second=0;
const float radius = 45.0;
const float xOrigin = 50.0;
const float yOrigin = 50.0;

//shamelessly stole this code for drawing a circle from:
//http://slabode.exofire.net/circle_draw.shtml
void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
	float theta = 2 * 3.1415926 / float(num_segments); 
	float tangetial_factor = tanf(theta);//calculate the tangential factor 
	float radial_factor = cosf(theta);//calculate the radial factor 
	float x = r;//we start at angle = 0 
	float y = 0; 
    
	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);//output vertex 
        
		//calculate the tangential vector 
		//remember, the radial vector is (x, y) 
		//to get the tangential vector we flip those coordinates and negate one of them 
		float tx = -y; 
		float ty = x; 
        
		//add the tangential vector 
		x += tx * tangetial_factor; 
		y += ty * tangetial_factor; 
        
		//correct using the radial factor 
		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
}

//this function will draw and animate the hands
void drawTime()
{
    glLineWidth(2);
	float secondsAngle = 2*PI*(second/60.0)+3*PI/2;
	float xNew = xOrigin+(radius-20)*cos (-secondsAngle);
	float yNew = yOrigin+(radius-20)*sin (-secondsAngle);
	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
		glVertex3f(xOrigin, yOrigin, 0.0);
		glVertex3f(xNew, yNew, 0.0);
	glEnd();
   
    glLineWidth(4);
    float minutesAngle = 2*PI*(minute/60.0)+3*PI/2;
    xNew = xOrigin+radius*cos (-minutesAngle);
	yNew = yOrigin+radius*sin (-minutesAngle);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	   glVertex3f(xOrigin, yOrigin, 0.0);
	   glVertex3f(xNew, yNew, 0.0);
	glEnd();
   
	float hoursAngle = 2*PI*(hour/12.0)+3*PI/2;
	xNew = xOrigin+(radius-20)*cos (-hoursAngle);
	yNew = yOrigin+(radius-20)*sin (-hoursAngle);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
	   glVertex3f(xOrigin, yOrigin, 0.0);
	   glVertex3f(xNew, yNew, 0.0);
	glEnd();
	
	glFlush(); 
}

//this function will keep our second, minute, and hour variables updated
//with the current time
void update(int ignored)
{
	time_t now;
	struct tm* timeinfo;
	time(&now);
	timeinfo = localtime(&now);
	hour = timeinfo->tm_hour;
	minute = timeinfo->tm_min;
	second = timeinfo->tm_sec;

	// tell glut to redraw the window
	glutPostRedisplay();
		
	// tell glut to call update again in 100 ms
	glutTimerFunc(100, update, 0); 
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

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	   
	glColor3f(0.0, 0.0, 0.0);
   	DrawCircle(50.0, 50.0, radius, 50);
   	
   	double pointsAngle=0;
   	glPointSize(5.0);
   	glColor3f(1.0, 1.0, 0);
   	for (int i=0; i<12; ++i) 
   	{
		float x = xOrigin+radius*cos (pointsAngle);
		float y = yOrigin+radius*sin (pointsAngle);
		glBegin(GL_POINTS);
			//upper right
			glVertex3f(x, y, 0.0);

			//lower left
		glEnd();
		
		pointsAngle=pointsAngle+(PI/6);
	}
   
	glFlush(); 
   
	drawTime();
}

// Main routine
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);

	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("clock2.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);  

	glewExperimental = GL_TRUE;
	glewInit();

	//setup
	glClearColor(1.0, 1.0, 1.0, 0.0); 
  
   
	glutTimerFunc(100, update, 0);
	glutMainLoop(); 

}
