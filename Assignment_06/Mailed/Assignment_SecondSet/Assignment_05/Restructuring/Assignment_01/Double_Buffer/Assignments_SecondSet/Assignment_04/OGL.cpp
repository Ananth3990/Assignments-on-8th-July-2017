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

void RenderTriangleMultiColoredVertex(GLfloat vert[][3], GLfloat color[][3])
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
	glColor3f(color[0][0], color[0][1], color[0][2]);
	glVertex3f(vert[0][0], vert[0][1], vert[0][2]);
	glColor3f(color[1][0], color[1][1], color[1][2]);
	glVertex3f(vert[1][0], vert[1][1], vert[1][2]);
	glColor3f(color[2][0], color[2][1], color[2][2]);
	glVertex3f(vert[2][0], vert[2][1], vert[2][2]);
	glEnd();
}

void display(void)
{
	void RenderTriangleMultiColoredVertex(GLfloat vert[][3], GLfloat color[][3]);

	typedef struct
	{
		GLfloat triangle_vert[3][3];
	}TRIANGLES;

	typedef struct
	{
		GLfloat color[3][3];
	}COLOR;

	TRIANGLES triangles;
	COLOR color;

	glClear(GL_COLOR_BUFFER_BIT);

	triangles = { { { -1.0f, -1.0f, 0.0f } ,{ 1.0f, -1.0f, 0.0f } ,{ 0.0f, 1.0f, 0.0f } } };
	color = { { { 1.0f, 0.0f, 0.0f } ,{ 0.0f, 1.0f, 0.0f } ,{ 0.0f, 0.0f, 1.0f } } };
	RenderTriangleMultiColoredVertex(triangles.triangle_vert, color.color);

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

