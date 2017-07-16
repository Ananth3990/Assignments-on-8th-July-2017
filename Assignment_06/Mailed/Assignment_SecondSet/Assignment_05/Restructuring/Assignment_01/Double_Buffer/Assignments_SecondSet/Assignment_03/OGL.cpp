#include <GL/freeglut.h>
#include<math.h>

//global variable declaration
bool bFullscreen=false; //variable to toggle for fullscreen


static const GLfloat pi = 3.1415f;

int main(int argc,char** argv)
{
	//function prototypes
	void display(void);
	void resize(int,int);
	void keyboard(unsigned char,int,int);
	void mouse(int,int,int,int);
	void initialize(void);
	void uninitialize(void);

	//code
	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800,600); //to declare initial window size
	glutInitWindowPosition(100,100); //to declare initial window position
	glutCreateWindow("OpenGL First Window : Hello World !!!"); //open the window with "OpenGL First Window : Hello World" in the title bar

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

//	return(0); 
}

void RenderPoint(GLfloat *point, GLfloat point_width, GLfloat *color)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(point_width);
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	glVertex3f(point[0], point[1], point[2]);
	glEnd();
}

void display(void)
{
	void RenderPoint(GLfloat *point, GLfloat point_width, GLfloat *color);

	typedef struct Point
	{
		GLfloat point[3];
	}point;

	typedef struct Color
	{
		GLfloat col[3];
	}color;

	point p;
	color colo;

	glClear(GL_COLOR_BUFFER_BIT);

	p = { 0.0f, 0.0f, 0.0f };
	colo = { 1.0f, 1.0f, 1.0f };
	RenderPoint(p.point, 10.0f, colo.col);

	p = { 0.0f, 0.5f, 0.0f };
	colo = { 1.0f, 1.0f, 0.0f };
	RenderPoint(p.point, 20.0f, colo.col);

	p = { 0.0f, -0.5f, 0.0f };
	colo = { 0.0f, 1.0f, 1.0f };
	RenderPoint(p.point, 30.0f, colo.col);

	//glFlush();
	glutSwapBuffers();
}

void initialize(void)
{
	//code
	//to select clearing (background) clear
	glClearColor(0.0f,0.0f,0.0f,0.0f); //blue 
}

void keyboard(unsigned char key,int x,int y)
{
	//code
	switch(key)
	{
	case 27: // Escape
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if(bFullscreen==false)
		{
			glutFullScreen();
			bFullscreen=true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen=false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button,int state,int x,int y)
{
	//code
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width,int height)
{
	// code
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void uninitialize(void)
{
	// code
}

