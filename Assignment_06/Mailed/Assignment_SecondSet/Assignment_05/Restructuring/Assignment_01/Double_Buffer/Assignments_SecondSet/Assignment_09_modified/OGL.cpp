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

	glutInitWindowSize(600,600); //to declare initial window size
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

void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color)
{
	GLfloat angle = 0.0f;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
	for (angle = 0.0f; angle <= (2.0f*pi); angle = angle + 0.001f)
	{
		glVertex3f((GLfloat)((rad*cos(angle)) + arr[0]), (GLfloat)((rad*sin(angle)) + arr[1]), arr[2]);
	}
	glEnd();
}

void display(void)
{
	void RenderCircle(GLfloat rad, GLfloat *arr, GLfloat *color);
	typedef struct
	{
		GLfloat carr[3];
	}circle;

	typedef struct
	{
		GLfloat carr[3];
	}color;

	circle cc;
	color cl;

	cc = { 0.0f,0.0f,0.0f };
	cl = { 1.0f,0.0f,0.0f };

	glClear(GL_COLOR_BUFFER_BIT);

	RenderCircle(1.0f, cc.carr, cl.carr);
	cl = { 1.0f,1.0f,0.0f };
	RenderCircle(0.9f, cc.carr, cl.carr);
	cl = { 0.0f,1.0f,1.0f };
	RenderCircle(0.8f, cc.carr, cl.carr);
	cl = { 0.0f,1.0f,0.0f };
	RenderCircle(0.7f, cc.carr, cl.carr);
	cl = { 0.0f,0.0f,1.0f };
	RenderCircle(0.6f, cc.carr, cl.carr);
	cl = { 0.50f,0.50f,0.50f };
	RenderCircle(0.5f, cc.carr, cl.carr);
	cl = { 0.275f,0.50f,0.50f };
	RenderCircle(0.4f, cc.carr, cl.carr);
	cl = { 1.0f,1.0f,1.0f };
	RenderCircle(0.3f, cc.carr, cl.carr);
	cl = { 1.0f,0.2768f,0.5f };
	RenderCircle(0.2f, cc.carr, cl.carr);
	cl = { 0.876f,0.2768f,0.0f };
	RenderCircle(0.1f, cc.carr, cl.carr);
	//RenderCircle(0.1f, 0.5f, 0.5f);

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

