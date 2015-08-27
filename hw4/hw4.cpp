///////////////////////////////////
// hw4.cpp
//
// OpenGL program to draw a square.
// Sumanta Guha and David Tulis
///////////////////////////////////

// to define exit(0)
#include <stdlib.h>

#ifdef __APPLE__
#  include <GL/glew.h>

#include <GLUT/glut.h>
#  include <GLUT/glut.h>

#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream> 
using namespace std;

//to seed our rng
static int x = (srand(time(NULL)), 10);

//mouse coordinates
double last_mouse_x;
double last_mouse_y;

//size of our openGL window
int width, height;			

static int inSelectionMode = 0; 
static int hits; 
static unsigned int buffer[1024]; 

enum ObjType { CUBE, TEAPOT, CONE, ICOSAHEDRON, SPHERE };

typedef struct
{
    ObjType type;

    float x;
    float y;
    float z;

    int selected;
} object;


static const int num_objects=40; 

static object objects[] =
        { 
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 }, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ SPHERE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 }, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ SPHERE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 }, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ SPHERE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 },
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0 }, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ SPHERE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0}, 
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ TEAPOT, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CUBE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ CONE, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		{ ICOSAHEDRON, rand()%11-4, rand()%-10-5, rand()%-45-35, 0},
		//{ CUBE, 0, 0, -10, 0 },
		//{ TEAPOT, -4, 0, -10, 0 },
		//{ CONE, 4, 0, -10, 0 },
		//{ CONE, -2, 5, -30, 0 }, 
		//{ ICOSAHEDRON, 4, 4, -10, 0}, 
		//{ SPHERE, 1, 1, -15, 0}, 
		//{ ICOSAHEDRON, -4, 0, -15, 0},
		//{ TEAPOT, 4, 5, -15, 0},
		//{ CUBE, 0, 0, -25, 0},
		//{ CONE, -3, 3, -15, 0},
		//{ ICOSAHEDRON, -4, -8, -25, 0},
        };

static float my_x=0;
static float my_y=0;
static float my_z=0;
static float my_angle=0;
static float my_angle_y=91;

void drawFloor()
{
    glColor3f(.5,.5,.5);
    glBegin(GL_POLYGON);
    glVertex3f(-100,-1,-100);
    glVertex3f(100,-1,-100);
    glVertex3f(100,-1,100);
    glVertex3f(-100,-1,100);
    glEnd();    
}

void drawObject(const object& o)
{
    glPushMatrix();
    glTranslatef(o.x, o.y, o.z);
    glLineWidth(1);

    if (o.selected==1)
    {
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {
        glColor3f(0.0, 1.0, 0.0);
    }

    switch (o.type)
    {
			case CUBE:
				glutSolidCube(1);
				glColor3f(0,0,0);
				glutWireCube(1);
				break;

     case TEAPOT:
			glutSolidTeapot(1);
			glColor3f(0,0,0);
			glutWireTeapot(1);
			break;

			case CONE:
			glTranslatef(0, -.5, 0);
			glRotatef(90, -1, 0, 0);
			glScalef(0.25, 0.25, 0.25);
			glutSolidCone(5, 10, 3, 3);
			glColor3f(0,0,0);
			glutWireCone(5, 10, 3, 3);
			break;
         
		case ICOSAHEDRON: 
		glTranslatef(0.2, 0.4, 0);
		glScalef(1.6, 1.6, 1.6);
		glutSolidIcosahedron();
		glColor3f(0,0,0);
		glutWireIcosahedron();
		break;
		
		case SPHERE: 
		glutSolidSphere(1.7, 50, 50);
		glColor3f(0,0,0);		
		glutWireSphere(1.7, 50, 50);
		break;
    }
    glPopMatrix();
}

void drawObjects()
{

	// calculate heading
    gluLookAt(
    my_x, 
    my_y, 
    my_z, 
    
    my_x - 5*sin((M_PI/180.0) * my_angle),  
    my_y - 5*cos((M_PI/180.0) * my_angle_y), 
    my_z - 5*cos((M_PI/180.0) * my_angle), 
    
    0, 
    1, 
    0);

	//drawFloor();

	for (int i=0; i<num_objects; i++)
    {
		if (inSelectionMode==1)
        {
			glLoadName(i);
		}
        drawObject(objects[i]);
    }
	//glutSwapBuffers();
	glutPostRedisplay();
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        
    //we want to put opengl in rendering mode
    inSelectionMode=0;
	
	drawObjects();

    glFlush();
}

void pickFunction(int button, int state, int x, int y)
{
	// Viewport data.
	int viewport[4]; 
	
	// Don't react unless left button is pressed.
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return; 
   
	// Get viewport data.
	glGetIntegerv(GL_VIEWPORT, viewport); 

	// Specify buffer to write hit records in selection mode
	glSelectBuffer(1024, buffer); 
	// Enter selection mode.
	(void) glRenderMode(GL_SELECT); 

	// Save the viewing volume defined in the resize routine.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
   
	//Define a viewing volume corresponding to selecting in 3 x 3 region around the cursor.
	glLoadIdentity();
	gluPickMatrix((float)x, (float)(viewport[3] - y), 3.0, 3.0, viewport);
       
	gluPerspective(50, 1, 0.1, 250);
   
	// Return to modelview mode before drawing.
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	glInitNames(); // Initializes the name stack to empty.
	glPushName(0); // Puts name 0 on top of stack.

	//Determine hits by calling redrawing objects so that names are assigned.
	inSelectionMode = 1;
	
	//redraw
	drawObjects();
        
    glPopName();
    // Return to rendering mode, returning number of hits.
    hits = glRenderMode(GL_RENDER); 

   // Determine closest of the hit objects (if any).
	if (hits > 0)
	{
		unsigned int* ptr = buffer;
		
		unsigned int smallestZ=*(ptr+1)+3;
		unsigned int stack_top;
		unsigned int minZ;
		unsigned int smallestStackTop=1000000;
		
		for (int i=0; i<hits; i++)
		{
			ptr++;
			minZ = *ptr;
			
			ptr +=2;
			stack_top = *ptr;
			//find smallest z value
			if (minZ<smallestZ)
			{
				smallestZ=minZ;
				smallestStackTop=stack_top;
			}
			
			ptr++;
		}
		
		if (objects[smallestStackTop].selected==0)
			objects[smallestStackTop].selected=1;
		else
			objects[smallestStackTop].selected=0;		
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	glutPostRedisplay();
}

// Initialization routine.
void setup(void) 
{
    glClearColor(1.0, 1.0, 1.0, 0.0); 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset( 1, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    float aspect = w*1.0/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, aspect, 0.1, 250);
	width=w;
	height=h;
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
		case 'd': 
			my_x+=sin(M_PI/180*(my_angle + 90));
			my_z+=cos(M_PI/180*(my_angle + 90));
			break;
		case 'a': 
			my_x-=sin(M_PI/180*(my_angle + 90));
			my_z-=cos(M_PI/180*(my_angle + 90));
			break;
		case 'w':
			my_x -= sin((M_PI/180.0)*my_angle);
			my_z -= cos((M_PI/180.0)*my_angle);
			break;
		case 's':
			my_x += sin((M_PI/180.0)*my_angle);
			my_z += cos((M_PI/180.0)*my_angle);
			break;
   }
   
    if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;
    
    glutPostRedisplay();
}

void trackMouse (int x, int y)
{
	last_mouse_x=x;
	last_mouse_y=height-y;
}

void mouseMotion()
{	
	//left right
	if (last_mouse_x<20) my_angle+=2;
	if (last_mouse_x>480) my_angle-=2;
	
	if (my_angle > 360.0) my_angle -= 360;
    if (my_angle < 0) my_angle += 360;
	
	//up down
	if (last_mouse_y>20) my_angle_y+=2;
	if (last_mouse_y<480) my_angle_y-=2;

	if (my_angle_y >= 180.0) my_angle_y = 180;
    if (my_angle_y < 75) my_angle_y = 75;

   glutPostRedisplay();
}

// Main routine.
int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH | GLUT_RGBA); 
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("colored objects");	
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(resize);  
	glutKeyboardFunc(keyInput);
	glutPassiveMotionFunc(trackMouse);
	glutIdleFunc(mouseMotion);
	glutMouseFunc(pickFunction); 

	glewExperimental = GL_TRUE;
	glewInit();

	setup(); 
   
	glutMainLoop(); 
}
